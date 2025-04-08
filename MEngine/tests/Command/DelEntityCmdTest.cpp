#include <gtest/gtest.h>
#include "Command/DelEntityCmd.h"

TEST(DelEntityCmdTest, ExecuteTest)
{
    // 测试删除命令执行
    // auto entity = std::make_shared<Entity>(...);
    // DelEntityCmd cmd(entity);
    // EXPECT_TRUE(cmd.execute());
    // EXPECT_FALSE(cmd.targetExists()); // 验证图元已被删除
}

TEST(DelEntityCmdTest, UndoTest)
{
    // 测试删除命令撤销
    // auto entity = std::make_shared<Entity>(...);
    // DelEntityCmd cmd(entity);
    // cmd.execute();
    // EXPECT_TRUE(cmd.undo());
    // EXPECT_TRUE(cmd.targetExists()); // 验证图元已恢复
}