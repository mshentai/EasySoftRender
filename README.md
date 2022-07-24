# EasySoftRenderer
 一个简单的软渲染器项目。
 ![Main](https://user-images.githubusercontent.com/72799938/180640858-0ece4800-b08e-488e-b050-51cf226e1774.png)
 
# 本项目意义
本项目的意义在于深入学习渲染管线的流程，在不使用图形API的情况下，实现对三维模型的渲染。

# 已实现目标
1、透视投影和透视校正每个顶点参数插值。

2、投影空间背面剔除。

3、采用 Clamp 纹理寻址实现纹理采样。

4、Z 缓冲（反转 z）和深度测试，用于 3D 渲染。

5、实现 Phong/Blinn-Phong 光照算法。

6、实现平面阴影效果。

![线框图](https://user-images.githubusercontent.com/72799938/180641949-07b58363-a0fb-4ae1-8802-5ac3a2aeb6e4.png)

![阴影](https://user-images.githubusercontent.com/72799938/180641941-a0459176-a2f8-4e05-924b-a4a6331aa2cf.png)

![Main](https://user-images.githubusercontent.com/72799938/180641952-20f74311-4f9f-447e-9634-390b25cfc700.png)

# 待实现目标
 1、透明度和混合操作

 2、阴影贴图（Shadow Map）的阴影效果+VSSM软阴影。
 
 3、实现多线程渲染。
 



