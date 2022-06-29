# 再想想

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0e46650d9fb4464d930cf8ad3e73f4a6)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=think-think-again/think-think&amp;utm_campaign=Badge_Grade)

## Instructions

Please set environment variable `QT_ENABLE_HIGHDPI_SCALING` to `0` before build.

## 游戏文档

1. 程序功能介绍：
    + 程序类型：包含剧情的三消类游戏。
    + 游戏名称：北京大学の不适合者~史上最强文科生转生后入学到信息科学技术学院！
    + 游戏主线：北京大学的学生小Z与三位老师之间的互动。
    + 游戏主体：一共有三关，每一关玩家都会遇到一个boss且boss难度不断上升。在过完剧情后，玩家可以通过消除宝石来对boss造成伤害、回复自己的生命值以及获得精神力来释放技能。玩家在战胜一个boss后会自动解锁下一段剧情。在对战中玩家还可以随时返回主菜单重新开始本关。

2. 项目各模块与类的设计细节：
    + 主窗口：我们添加了一个主窗口，开始菜单、剧情以及战斗都可以分别在上面显示。我们这里使用到QStackedLayout布局控件，来创建各个板块的窗口以及实现窗口之间的变换。
    + 开始菜单：使用ps做出背景图片，在开始菜单上添加start以及exit按钮来开始或者退出游戏。
    + 剧情模块：先设计好各关的剧情，在将剧情根据boss的名称转为三个文档，并用json格式存储，然后在代码里用循环来控制剧情的播放。在对话框方面，采用半透明对话框，并且保证每个人说话时都有对应的头像且使用鼠标单击任意位置便可继续剧情。
    + 战斗界面：战斗界面由游戏面板（供玩家操作的部分）、技能按钮、boss、玩家血量及精神力、回合数以及返回菜单按钮组成
        * 游戏面板：上面一开始会随机生成四种不同样式的宝石，经过玩家的操作消除部分宝石后可以从上掉落新的普通宝石。三个以上的普通宝石还可以合成相对应的升级宝石或者S宝石，不同的宝石对应着不同的效果。宝石可以上下左右移动，但只有满足消除的规则时移动才是允许的。S宝石可以右键消除并释放强大力量。
        * 技能按钮：一共有四个技能，均继承于skill类。每个技能都有介绍，在鼠标移到技能图标上时会显示。
        * boss：所有boss都共用一个boss类，其中包含了它们名称、血量以及对应的立绘。每个boss的难度不同，而且和玩家一样，boss们还有属于自己的技能。boss的血量我们采用的是QProgressBar来显示。
        * 玩家血量及精神力：和boss的血量一样，我们都采用了QProgressBar来显示。
        * 回合数：我们采用label来显示，每经过一次成功的交换，当前回合数便会加一。
        * 返回菜单按钮：和start按钮和exit按钮一样，点击它便可以返回到主菜单。
    
3. 小组成员的分工情况：
    + 开始菜单的设计：屠学畅、朱蔚骐、俞俊喆
    + 剧情的设计与实现：俞俊喆、屠学畅
    + boss设计：朱蔚骐
    + 返回主菜单按钮设计：俞俊喆
    + S宝石右键消除：俞俊喆