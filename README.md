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

一共有三关，每一关包含小Z与一个老师（Boss）的剧情，剧情结束后进入挑战，玩家可以通过消除宝石来对 Boss 造成伤害、回复自己的生命值以及获得精神力来释放技能。三个关卡挑战难度逐渐上升。玩家在战胜一个 Boss 后会自动解锁下一段剧情。在对战中玩家还可以随时返回主菜单重新开始本关。

#### 特色

*   适配了所有屏幕分辨率。
*   部分素材支持高达 8K（7680 x 4320）的分辨率
*   立绘由 [This Anime Does Not Exist](https://thisanimedoesnotexist.ai/) 生成。
*   背景音乐为 CC0 许可。


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

*   包含游戏面板（GameBoard 类）、玩家（Player 类）、Boss（Boss 类）和一个返回主菜单按钮（StartButton 类）。
*   包含四个玩家技能（Skill 类的派生类）。
*   包含三个用于展示 Boss 生命值、玩家生命值、玩家精神力的 QProgressBar 和一个用于展示当前回合数的 QLabel。自定义了样式。
*   使用了半透明白色遮罩覆盖背景图片，突出画面主体。

##### 游戏面板类（GameBoard）

继承自 QObject 和 QGraphicsPixmapItem。

设计细节：

*   包含 $8\times 7$ 的网格，初始随机生成四种不同样式的普通宝石（Gem 类）。
*   不同宝石对应着不同的消除效果，包括：物理攻击、魔法攻击、回复生命值、回复精神力。
*   玩家操作消除部分宝石后可以从上方掉落新的普通宝石。
*   一部分消除模式会合成四种升级宝石或者S宝石。
*   宝石可以上下左右移动，但只有满足消除的规则时移动才是允许的。
*   S宝石还可以右键消除并释放强大力量。

##### 宝石类（Gem）

继承自 QObject 和 QGraphicsPixmapItem。

设计细节：

*   读取对应宝石图片并显示。
*   重新实现了 mousePressEvent、mouseReleaseEvent和mouseMoveEvent 函数，鼠标长按时显示宝石不断放大缩小的动画，并且和游戏面板共同完成拖动和消除宝石的动画效果。
*   重新实现了 hoverEnterEvent 和 hoverLeaveEvent 函数，鼠标悬浮时显示宝石晃动的动画。

##### 玩家类（Player）

继承自 QObject。

设计细节：

*   记录了玩家的生命值和精神力。

##### Boss类（Boss）

继承自 QObject 和 QGraphicsPixmapItem。

设计细节：

*   所有 Boss 共用一个 Boss 类。
*   记录 Boss 的生命值、物理防御和魔法防御。
*   展示 Boss 的立绘，并且添加了上下浮动的动画效果，使 Boss 栩栩如生。
*   在战斗结束（包括失败或胜利）时，Boss 立绘会停止浮动，并且逐渐变为透明。

##### 技能类（Skill、Skill[1-4]、SkillHoverLayer）

Skill、SkillHoverLayer 继承自 QObject 和 QGraphicsPixmapItem，Skill[1-4] 继承自 Skill。

设计细节：

*   Skill 类展示技能图片。
*   SkillHoverLayer 类检测鼠标事件，重新实现了 hoverEnterEvent 和 hoverLeaveEvent 函数，鼠标悬浮达到一定时长显示对应技能介绍（QLabel 类）。技能介绍自定义了样式，且跟随鼠标移动直到离开技能图片。
*   重新实现 mousePressEvent 函数，在点击技能时做出相应反馈。
*   特殊的技能需要指定一个宝石，通过与宝石类交互实现了这个功能。



### 小组成员的分工情况

主菜单设计：屠学畅、朱蔚骐、俞俊喆

剧情的设计与实现：俞俊喆、屠学畅

Boss 设计：朱蔚骐

游戏机制设计与实现：朱蔚骐、俞俊喆

伤害结算系统设计与实现：朱蔚骐

技能设计与实现：屠学畅、朱蔚骐、俞俊喆

主窗口类：屠学畅

动画设计与实现：屠学畅

游戏整体界面处理、屏幕比例适配：屠学畅

宝石美术设计：朱蔚骐

宝石交互设计：屠学畅

图像文件处理：屠学畅、朱蔚骐、俞俊喆

背景音乐：屠学畅、朱蔚骐、俞俊喆

### 项目的总结与反思

*   这是我们小组成员第一次使用QT进行项目的设计与实现，总体上来说这个项目最后的呈现效果大致符合我们小组的预期。
*   在项目的选题上，我们为了保证一定的趣味性，选择了用QT做一个小游戏。而在游戏主体玩法方面，我们经过讨论，结合市面上有的游戏，选择了三消这一不至于很难实现但又有一定的挑战性的游戏玩法。在我们参考了部分游戏后，选择将游戏与剧情相结合起来，在保证游戏有挑战性的同时，增加了不少趣味性。
*   但由于这是我们小组成员第一次使用QT进行游戏设计，对QT某些控件及功能的了解还不到位，导致有些时候会采取相对复杂的方法，增加了代码的长度。不过考虑到这是我们第一次接触QT，而且最后都能实现相应的功能，这样的结果也变得可以接受了。
*   在此次的项目制作上，我们对QT有了一个更深入的了解，也对作为一个团队进行游戏制作有了一个初步的概念，相信这对我们未来的学习甚至是工作都会有一定的帮助。