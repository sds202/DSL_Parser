##### 关于项目
1. 使用git进行版本控制
2. 使用较为现代的C++语法（如C++20的modules和协程等）
3. 支持DSL脚本的热切换
4. 较为完善的并发处理系统
5. 使用了很多的库，第一次编写含有较多外部库的稍大型程序

##### 其他说明
依赖，需要自行安装：

1. drogon
2. antlr
3. jsoncpp
4. openssl


DSL_Parser（主程序）

其中的DAO.ixx是数据库测试桩

DSL文件位于其中的DSL_script文件夹下，其中包括测试用dsl文件。


Admin_interface（运维人员交互程序）


User_interface（用户交互程序）


Test_auto（自动测试程序）

其中的MockLLM文件夹下是LLM测试桩

其余是测试驱动，测试驱动使用方法见报告


Tests_concurrent（一个意义不大的并发测试程序）

其中包括相应的测试驱动和测试桩
