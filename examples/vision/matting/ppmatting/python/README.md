# PPMatting Python部署示例

在部署前，需确认以下两个步骤

- 1. 软硬件环境满足要求，参考[FastDeploy环境要求](../../../../../docs/the%20software%20and%20hardware%20requirements.md)  
- 2. FastDeploy Python whl包安装，参考[FastDeploy Python安装](../../../../../docs/quick_start)

本目录下提供`infer.py`快速完成Unet在CPU/GPU，以及GPU上通过TensorRT加速部署的示例。执行如下脚本即可完成

```bash
#下载部署示例代码
git clone https://github.com/PaddlePaddle/FastDeploy.git
cd FastDeploy/examples/vision/matting/ppmatting/python

# 下载Unet模型文件和测试图片
wget https://bj.bcebos.com/paddlehub/fastdeploy/PP-Matting-512.tgz
tar -xvf PP-Matting-512.tgz
wget https://raw.githubusercontent.com/DefTruth/lite.ai.toolkit/main/examples/lite/resources/test_lite_matting_input.jpg
wget https://raw.githubusercontent.com/DefTruth/lite.ai.toolkit/main/examples/lite/resources/test_lite_matting_bgr.jpg
# CPU推理
python infer.py --model PP-Matting-512 --image test_lite_matting_input.jpg --bg test_lite_matting_bgr.jpg --device cpu
# GPU推理 (TODO: ORT-GPU 推理会报错)
python infer.py --model PP-Matting-512 --image test_lite_matting_input.jpg --bg test_lite_matting_bgr.jpg --device gpu
# GPU上使用TensorRT推理 （注意：TensorRT推理第一次运行，有序列化模型的操作，有一定耗时，需要耐心等待）
python infer.py --model PP-Matting-512 --image test_lite_matting_input.jpg --bg test_lite_matting_bgr.jpg --device gpu --use_trt True
```

运行完成可视化结果如下图所示
<div width="700">
<img width="220" float="left" src="https://user-images.githubusercontent.com/67993288/184301892-457f7014-2dc0-4ad1-b688-43b41fac299a.jpg">
<img width="220" float="left" src="https://user-images.githubusercontent.com/67993288/184301871-c234dfdf-3b3d-46e4-8886-e1ac156c9e4a.jpg">
<!-- <img width="220" float="left" src="https://user-images.githubusercontent.com/67993288/184321622-d9a494c3-72f3-47f1-97c5-8a2372de491f.JPG"> -->
</div>

## PaddleMatting Python接口

```python
fd.vision.matting.PaddleMatting(model_file, params_file, config_file, runtime_option=None, model_format=Frontend.PADDLE)
```

PPMatting模型加载和初始化，其中model_file, params_file以及config_file为训练模型导出的Paddle inference文件，具体请参考其文档说明[模型导出](https://github.com/PaddlePaddle/PaddleSeg/tree/release/2.6/Matting)

**参数**

> * **model_file**(str): 模型文件路径
> * **params_file**(str): 参数文件路径
> * **config_file**(str): 推理部署配置文件
> * **runtime_option**(RuntimeOption): 后端推理配置，默认为None，即采用默认配置
> * **model_format**(Frontend): 模型格式，默认为Paddle格式

### predict函数

> ```python
> PaddleMatting.predict(input_image)
> ```
>
> 模型预测结口，输入图像直接输出检测结果。
>
> **参数**
>
> > * **input_image**(np.ndarray): 输入数据，注意需为HWC，BGR格式

> **返回**
>
> > 返回`fastdeploy.vision.MattingResult`结构体，结构体说明参考文档[视觉模型预测结果](../../../../../docs/api/vision_results/)

### 类成员属性
#### 预处理参数
用户可按照自己的实际需求，修改下列预处理参数，从而影响最终的推理和部署效果



## 其它文档

- [PPMatting 模型介绍](..)
- [PPMatting C++部署](../cpp)
- [模型预测结果说明](../../../../../docs/api/vision_results/)