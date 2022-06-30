# 北京大学の不适合者~史上最强文科生转生后入学到信息科学技术学院！

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0e46650d9fb4464d930cf8ad3e73f4a6)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=think-think-again/think-think&amp;utm_campaign=Badge_Grade)

## Instructions

Please set environment variable `QT_ENABLE_HIGHDPI_SCALING` to `0` before build.

## 游戏文档

### 程序功能介绍：

#### 程序类型

带有剧情的三消类游戏。

#### 游戏名称

北京大学の不适合者~史上最强文科生转生后入学到信息科学技术学院！

#### 游戏主线

北京大学的学生小Z与三位老师之间的互动。

#### 游戏主体

一共有三关，每一关包含小Z与一个老师的剧情，剧情结束后进入挑战，玩家可以通过消除宝石来对老师造成伤害、回复自己的生命值以及获得精神力来释放技能。三个关卡挑战难度逐渐上升。玩家在战胜一个老师后会自动解锁下一段剧情。在对战中玩家还可以随时返回主菜单重新开始本关。

### 项目各模块与类的设计细节

#### 主窗口类（MyWindow）

继承自 QWidget。

功能：

*   处理主菜单、剧情以及战斗三个模块的事件，使用 QStackedLayout 来控制相应的切换。
*   循环播放背景音乐。

#### 主菜单模块

进入游戏的初始界面。

##### 主菜单类（MainMenu）

继承自 QGraphicsScene。

设计细节：

*   两个按钮（StartButton 类）分别用于开始游戏和退出游戏。

##### 按钮类（StartButton）

继承自 QObject 和 QGraphicsPixmapItem。

设计细节：

*   读取预先制作的按钮图片。
*   重新实现了 hoverEnterEvent 和 hoverLeaveEvent 函数响应鼠标悬浮动作，使用 QPropertyAnimation 制作了动画，在鼠标进入时略微放大图像，在鼠标离开时缩小回原先尺寸。
*   重新实现了 mousePressEvent，使用 signal 的方式允许外部程序绑定点击事件。

#### 剧情模块

将设计好的剧情使用 JSON 格式存储，使用代码读取并展示。三部分的剧情使用统一的代码，仅有 JSON 文件不同。

##### 剧情场景类（Dialogue）

继承自 QGraphicsScene。

设计细节：

*   读取 JSON 文件，使用自定义字体和其它样式的 QLabel 来展示剧情。
*   根据说话者不同分别展示预先制作的半透明对话框背景图片。
*   重新实现了 mousePressEvent 函数响应鼠标，单击任意位置即可继续剧情。
*   使用 QTimer 定时器实现了一段话中文字逐个出现的效果。
*   在文字尚未完全展示时屏蔽鼠标操作，避免非预期输入。

#### 战斗模块

##### 战斗场景类（BattleScene）

继承自 QGraphicsScene。

设计细节：

*   包含游戏面板（GameBoard 类）、玩家（Player 类）、老师（Boss 类）和一个返回主菜单按钮（StartButton 类）。
*   包含四个玩家技能（Skill 类的派生类）。
*   包含三个用于展示老师生命值、玩家生命值、玩家精神力的 QProgressBar 和一个用于展示当前回合数的 QLabel。自定义了样式。
*   使用了半透明白色遮罩覆盖背景图片，突出画面主体。

##### 游戏面板类（GameBoard）

继承自 QObject 和 QGraphicsPixmapItem。

设计细节。

*   包含 $8\times 7$ 的网格，初始随机生成四种不同样式的普通宝石（Gem 类）。
*   不同宝石对应着不同的消除效果，包括：物理攻击、魔法攻击、回复生命值、回复精神力。
*   玩家操作消除部分宝石后可以从上方掉落新的普通宝石。
*   一部分消除模式会合成四种升级宝石或者S宝石。
*   宝石可以上下左右移动，但只有满足消除的规则时移动才是允许的。
*   S宝石还可以右键消除并释放强大力量。

        * 技能按钮：一共有四个技能，均继承于skill类。每个技能都有介绍，在鼠标移到技能图标上时会显示。
        * boss：所有boss都共用一个boss类，其中包含了它们名称、血量以及对应的立绘。每个boss的难度不同，而且和玩家一样，boss们还有属于自己的技能。boss的血量我们采用的是QProgressBar来显示。
        * 玩家血量及精神力：和boss的血量一样，我们都采用了QProgressBar来显示。
        * 回合数：我们采用label来显示，每经过一次成功的交换，当前回合数便会加一。
        * 返回菜单按钮：和start按钮和exit按钮一样，点击它便可以返回到主菜单。
    
1. 小组成员的分工情况：
    + 开始菜单的设计：屠学畅、朱蔚骐、俞俊喆
    + 剧情的设计与实现：俞俊喆、屠学畅
    + boss设计：朱蔚骐
    + 返回主菜单按钮设计：俞俊喆
    + S宝石右键消除：俞俊喆