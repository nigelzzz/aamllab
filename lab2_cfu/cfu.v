// Copyright 2021 The CFU-Playground Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



module Cfu (
  input               cmd_valid,
  output              cmd_ready,
  input      [9:0]    cmd_payload_function_id,
  input      [31:0]   cmd_payload_inputs_0,
  input      [31:0]   cmd_payload_inputs_1,
  output reg              rsp_valid,
  input               rsp_ready,
  output reg    [31:0]   rsp_payload_outputs_0,
  input               reset,
  input               clk
);
    // Decode function ID.
    wire [6:0] funct7 = cmd_payload_function_id[9:3];
 // Registers holding offsets supplied from software.
    reg signed [15:0] InputOffset;
    reg signed [15:0] FilterOffset;
    // Sign-extend packed byte lanes and add offsets.
    wire signed [15:0] input_lane0 = $signed({{8{cmd_payload_inputs_0[7]}}, cmd_payload_inputs_0[7:0]}) + InputOffset;
    wire signed [15:0] input_lane1 = $signed({{8{cmd_payload_inputs_0[15]}}, cmd_payload_inputs_0[15:8]}) + InputOffset;
    wire signed [15:0] input_lane2 = $signed({{8{cmd_payload_inputs_0[23]}}, cmd_payload_inputs_0[23:16]}) + InputOffset;
    wire signed [15:0] input_lane3 = $signed({{8{cmd_payload_inputs_0[31]}}, cmd_payload_inputs_0[31:24]}) + InputOffset;

    wire signed [15:0] filter_lane0 = $signed({{8{cmd_payload_inputs_1[7]}}, cmd_payload_inputs_1[7:0]}) + FilterOffset;
    wire signed [15:0] filter_lane1 = $signed({{8{cmd_payload_inputs_1[15]}}, cmd_payload_inputs_1[15:8]}) + FilterOffset;
    wire signed [15:0] filter_lane2 = $signed({{8{cmd_payload_inputs_1[23]}}, cmd_payload_inputs_1[23:16]}) + FilterOffset;
    wire signed [15:0] filter_lane3 = $signed({{8{cmd_payload_inputs_1[31]}}, cmd_payload_inputs_1[31:24]}) + FilterOffset;

    // SIMD multiply step: four MACs per instruction.
    wire signed [31:0] prod_0 = input_lane0 * filter_lane0;
    wire signed [31:0] prod_1 = input_lane1 * filter_lane1;
    wire signed [31:0] prod_2 = input_lane2 * filter_lane2;
    wire signed [31:0] prod_3 = input_lane3 * filter_lane3;

    wire signed [31:0] sum_prods = prod_0 + prod_1 + prod_2 + prod_3;

    // Only not ready for a command when we have a response pending.
    assign cmd_ready = ~rsp_valid;

    always @(posedge clk) begin 
        if (reset) begin
            rsp_valid <= 1'b0;
            rsp_payload_outputs_0 <= 32'd0;
            InputOffset <= 16'sd0;
            FilterOffset <= 16'sd0;
        end else begin
            // Clear response once the host accepts it.
            if (rsp_valid && rsp_ready) begin
                rsp_valid <= 1'b0;
            end

            if (cmd_valid && cmd_ready) begin
                case (funct7)
                    7'd0: begin
                        rsp_payload_outputs_0 <= sum_prods;
                        rsp_valid <= 1'b1;
                    end
                    7'd1: begin
                        InputOffset <= cmd_payload_inputs_0[15:0];
                        rsp_payload_outputs_0 <= 32'd0;
                        rsp_valid <= 1'b1;
                    end
                    7'd2: begin
                        FilterOffset <= cmd_payload_inputs_0[15:0];
                        rsp_payload_outputs_0 <= 32'd0;
                        rsp_valid <= 1'b1;
                    end
                    default: begin
                        rsp_payload_outputs_0 <= 32'd0;
                        rsp_valid <= 1'b1;
                    end
                endcase
            end
        end
    end
endmodule


