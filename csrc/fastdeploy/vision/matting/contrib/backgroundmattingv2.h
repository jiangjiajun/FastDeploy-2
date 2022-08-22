// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include "fastdeploy/fastdeploy_model.h"
#include "fastdeploy/vision/common/processors/transform.h"
#include "fastdeploy/vision/common/result.h"

namespace fastdeploy {

namespace vision {

namespace matting {

class FASTDEPLOY_DECL BackgroundMattingv2 : public FastDeployModel {
 public:
  // 当model_format为ONNX时，无需指定params_file
  // 当model_format为Paddle时，则需同时指定model_file & params_file
  BackgroundMattingv2(const std::string& model_file,
                      const std::string& params_file = "",
                      const RuntimeOption& custom_option = RuntimeOption(),
                      const Frontend& model_format = Frontend::ONNX);

  // 定义模型的名称
  std::string ModelName() const { return "matting/BackgroundMattingv2"; }

  // 以下为一些可供用户修改的属性
  // tuple of (width, height), default (256, 256)
  std::vector<int> size;
  // 归一化的 alpha 和 beta，x'=x*alpha+beta
  std::vector<float> alpha;
  std::vector<float> beta;
  // whether to swap the B and R channel, such as BGR->RGB, default true.
  bool swap_rb;

  // 模型预测接口，即用户调用的接口
  // im 为用户的输入数据，目前对于CV均定义为cv::Mat
  // result 为模型预测的输出结构体
  bool Predict(cv::Mat* im, MattingResult* result);

 private:
  // 初始化函数，包括初始化后端，以及其它模型推理需要涉及的操作
  bool Initialize();

  // 输入图像预处理操作
  // Mat为FastDeploy定义的数据结构
  // FDTensor为预处理后的Tensor数据，传给后端进行推理
  bool Preprocess(Mat* mat, FDTensor* output,
                  std::map<std::string, std::array<int, 2>>* im_info);

  // 后端推理结果后处理，输出给用户
  // infer_result 为后端推理后的输出Tensor
  // result 为模型预测的结果
  bool Postprocess(std::vector<FDTensor>& infer_result, MattingResult* result,
                   const std::map<std::string, std::array<int, 2>>& im_info);

  void BackgroundMattingv2::StrideCheck(Mat* mat,
                                        const std::vector<float>& color);

  bool is_dynamic_input_;

  bool is_default_size_;
};

}  // namespace matting
}  // namespace vision
}  // namespace fastdeploy
