/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/shape_inference.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"

using ::tensorflow::int32;

class ExpectedValueOp : public tensorflow::OpKernel {
 public:
  explicit ExpectedValueOp(tensorflow::OpKernelConstruction* context)
      : tensorflow::OpKernel(context) {}

  void Compute(tensorflow::OpKernelContext* ctx) override {}
};

REGISTER_KERNEL_BUILDER(
    Name("ExpectedValueOp").Device(::tensorflow::DEVICE_CPU), ExpectedValueOp);

REGISTER_OP("ExpectedValueOp")
    .Input("attention_logits: float32")
    .Input("values: float32")
    .Output("evalue: float32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
      auto batch_size = c->Dim(c->input(0), 0);
      auto feature_size = c->Dim(c->input(0), 2);
      c->set_output(0, c->MakeShape({batch_size, feature_size}));
      return tensorflow::Status::OK();
    })
    .Doc(R"doc(
Dummy pooling op.
)doc");

class LayerNormOp : public tensorflow::OpKernel {
 public:
  explicit LayerNormOp(tensorflow::OpKernelConstruction* context)
      : tensorflow::OpKernel(context) {}

  void Compute(tensorflow::OpKernelContext* ctx) override {}
};

REGISTER_KERNEL_BUILDER(Name("LayerNorm").Device(::tensorflow::DEVICE_CPU),
                        LayerNormOp);

REGISTER_OP("LayerNorm")
    .Input("tensor: float32")
    .Input("scale: float32")
    .Input("offset: float32")
    .Input("axes: int32")
    .Output("result: float32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
      c->set_output(0, c->input(0));
      return tensorflow::Status::OK();
    })
    .Doc(R"doc(
Dummy layer norm op.
)doc");
