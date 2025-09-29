#include "models/ds_cnn_stream_fe/ds_cnn.h"
#include <stdio.h>
#include "menu.h"
#include "models/ds_cnn_stream_fe/ds_cnn_stream_fe.h"
#include "tflite.h"
#include "models/label/label0_board.h"
#include "models/label/label1_board.h"
#include "models/label/label6_board.h"
#include "models/label/label8_board.h"
#include "models/label/label11_board.h"
#include <inttypes.h>
#include <string.h>
#include <cstring>
// Initialize everything once
// deallocate tensors when done
static void ds_cnn_stream_fe_init(void) {
  tflite_load_model(ds_cnn_stream_fe, ds_cnn_stream_fe_len);
}

// TODO: Implement your design here
/*
static void run_with_title_and_input(const char* title,
                                     const float* data, size_t n) {
  printf("\n[%s]\n", title);
  feed_input_from_floats(data, n);
  if (tflite_invoke() != kTfLiteOk) {
    printf("Invoke failed\n");
    return;
  }
  dump_output_hex();
}
*/

static void run_zeros() {

}
static void run_label0()  {
     tflite_set_input_float(label0_data);
    printf("Running label 0\n");
    tflite_classify();

  // Process the inference results.
    float* output = tflite_get_output_float();
    for (int i = 0; i< 12; i++)
    {
        uint32_t bits;
            memcpy(&bits, &output[i], sizeof(bits)); // 取出 float 的 bit-pattern
        printf("%2d: 0x%08" PRIx32 "\n", i, bits);
        //printf("%2d : %f\n", i, output[i]);
    }

}
static void run_label1()  {
    tflite_set_input_float(label1_data);
    printf("Running label 1\n");
    tflite_classify();

  // Process the inference results.
    float* output = tflite_get_output_float();
    for (int i = 0; i< 12; i++)
    {
        uint32_t bits;
            memcpy(&bits, &output[i], sizeof(bits)); // 取出 float 的 bit-pattern
        printf("%2d: 0x%08" PRIx32 "\n", i, bits);
        //printf("%2d : %f\n", i, output[i]);
    }

}
static void run_label6()  {
    //run_with_title_and_input("label6",  label6_data,  label6_data_len);
    tflite_set_input_float(label6_data);
    printf("Running label 6\n");
    tflite_classify();

  // Process the inference results.
    float* output = tflite_get_output_float();
    for (int i = 0; i< 12; i++)
    {
        uint32_t bits;
            memcpy(&bits, &output[i], sizeof(bits)); // 取出 float 的 bit-pattern
        printf("%2d: 0x%08" PRIx32 "\n", i, bits);
        //printf("%2d : %f\n", i, output[i]);
    }
}
static void run_label8()  {
    //run_with_title_and_input("label8",  label8_data,  label8_data_len);

    tflite_set_input_float(label8_data);
    printf("Running label 8\n");
    tflite_classify();

  // Process the inference results.
    float* output = tflite_get_output_float();
    for (int i = 0; i< 12; i++)
    {
        uint32_t bits;
            memcpy(&bits, &output[i], sizeof(bits)); // 取出 float 的 bit-pattern
        printf("%2d: 0x%08" PRIx32 "\n", i, bits);
        //printf("%2d : %f\n", i, output[i]);
    }
}
static void run_label11() {
    //run_with_title_and_input("label11", label11_data, label11_data_len);
    tflite_set_input_float(label11_data);
    printf("Running label 11\n");
    tflite_classify();

  // Process the inference results.
    float* output = tflite_get_output_float();
    for (int i = 0; i< 12; i++)
    {
        uint32_t bits;
            memcpy(&bits, &output[i], sizeof(bits)); // 取出 float 的 bit-pattern
        printf("%2d: 0x%08" PRIx32 "\n", i, bits);
        //printf("%2d : %f\n", i, output[i]);
    }
}

static struct Menu MENU = {
    "Tests for ds_cnn_stream_fe",
    "ds_cnn_stream_fe",
    {
        MENU_ITEM('1', "Run with zeros input", run_zeros),
        MENU_ITEM('2', "Run with label0",      run_label0),
        MENU_ITEM('3', "Run with label1",      run_label1),
        MENU_ITEM('4', "Run with label6",      run_label6),
        MENU_ITEM('5', "Run with label8",      run_label8),
        MENU_ITEM('6', "Run with label11",     run_label11),
        MENU_END,
    },
};

// For integration into menu system
void ds_cnn_stream_fe_menu() {
  ds_cnn_stream_fe_init();
  menu_run(&MENU);
}
