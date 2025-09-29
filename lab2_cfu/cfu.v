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
   reg [8:0] InputOffset, FilterOffset;

    // SIMD multiply step:
    wire signed [15:0] prod_0, prod_1, prod_2, prod_3;
    assign prod_0 = 
    assign prod_1 = 
    assign prod_2 = 
    assign prod_3 = 

    wire signed [31:0] sum_prods;
    assign sum_prods = prod_0 + prod_1 + prod_2 + prod_3;

    // Only not ready for a command when we have a response.
    assign cmd_ready = ~rsp_valid;

    always @(posedge clk) begin
        if () begin

        end

    end	          
endmodule


