- 以 MainWindow 作为主窗口类：class MainWindow : public QMainWindow

里面嵌套了一个  m_tabView ：
m_tabView = new QTabWidget(this);
setCentralWidget(m_tabView);

以及还有一些工具条： 绘图工具条  编辑工具条  显示工具条  帮助工具条  状态栏 等

- 在 m_tabView 中添加了一个 viewWrapper：
class ViewWrapper : public QWidget

int index = m_tabView->addTab(viewWrapper, tr("View %1").arg(m_tabView->count() + 1));
m_tabView->setCurrentIndex(index);

鼠标交互都在 viewWrapper 中处理.

- 在 viewWrapper 又有两个成员变量：  m_glView（MarchView，用于渲染）和 m_scene（Scene，用于数据管理）。
m_glView = new MRender::MarchView(this);
m_scene = new MEngine::Scene();

m_glView 则是用来做渲染的：
class MRENDER_API MarchView : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core


m_scene 是一个普通的类， 它里面又有一些成员变量 主要用于数据的管理
尤其是有一個矩阵变量 matOrtho, viewWrapper对视图缩放移动等操作都在这个矩阵变量 matOrtho 上进行
然后再将这個 matOrtho 传递给 m_glView 进行渲染。


且 Scene 和 MarchView 都是在另一个DLL中的类， 

我现在在MainWindow 中有一个工具栏， 点击上面的按钮后， 会进行 点/线/圆/矩形 的绘制， 然后再点击 编辑 按钮， 就可以对这些点/线/圆/矩形进行移动， 缩放， 旋转等操作。
我现在的问题是，这些点/线/圆/矩形的绘制都是在 m_scene 中进行的，而且每种图元的绘制方式都是通过鼠标交互来实现的， 如何将这些操作进行区分





-------------------------------------------------
1. 数据与渲染分离
Scene 类可以作为数据管理的核心，负责存储和管理所有的对象（如 PolyLine、Point、Text 等）。Scene 不应直接涉及渲染。

MarchView 作为渲染类，负责从 Scene 中获取数据并绘制。它只与渲染相关，处理 OpenGL 的细节。

2. 事件传递与交互
用户在 MarchView 中进行选择、拖动等操作时，可以在 MarchView 内部捕获鼠标事件（如 mousePressEvent、mouseMoveEvent、mouseReleaseEvent），然后通过信号与 Scene 类交互，修改数据。

比如，鼠标点击选择某个对象时，MarchView 可以通过信号将选中的对象索引或者信息传递给 Scene，Scene 更新选中的对象，并通知 MarchView 刷新界面。

3. 控制层（Controller）
在 MainWindow 类中可以作为控制层，负责协调 Scene 与 MarchView 之间的交互。例如，用户在 UI 上点击按钮或进行其他操作时，MainWindow 可以通知 Scene 或 MarchView 执行相应操作（如添加、删除对象，或者开始移动操作）。

4. 对象选择与移动
选择操作：MarchView 需要实现一个选择框或拾取机制，通过鼠标点击来选择数据。选择后，可以通过信号将被选中的对象传递给 Scene，Scene 存储选中的对象。

移动操作：在 Scene 中保存选中的对象后，用户可以通过鼠标拖动来改变其位置。MarchView 捕获鼠标移动事件，然后更新 Scene 中对象的位置。当位置改变时，MarchView 会重新渲染。

5. 数据流转
使用信号与槽来传递事件。例如，MarchView 中的选择和移动操作可以通过信号通知 Scene 更新数据，而 Scene 更新数据后又通知 MarchView 重新渲染。

6. 示例架构
Scene：管理所有数据（如 PolyLine、Circle 等对象），提供方法获取、修改对象，选择与操作数据。

MarchView：渲染界面，接收来自 Scene 的数据并绘制，响应用户输入（选择、移动等）并通过信号与 Scene 交互。

MainWindow：作为控制层，协调不同部件的操作，初始化 Scene 和 MarchView，并提供 UI 元素与操作逻辑。

通过这种方式，你的 Scene 和 MarchView 的职责非常清晰：Scene 负责数据和状态管理，MarchView 负责显示和用户交互，而 MainWindow 充当协调者，确保各部分能够协同工作。

---------------------------------------
Scene：负责数据管理，维护需要渲染的对象（如几何数据、位置、状态等）。它应该是一个纯数据模型，不关心渲染细节。

MarchView：负责基于OpenGL的渲染，接收Scene的数据并将其可视化。它只负责绘制，不直接修改数据。

ViewWrapper：作为Scene和MarchView的“协调者”，处理用户交互（如选择、移动）并更新Scene中的数据，同时通知MarchView刷新渲染。

MainWindow：管理选项卡视图的整体布局和生命周期，不深入参与具体的交互逻辑。

这种设计遵循MVC（模型-视图-控制器）的思想：
Scene是模型（Model）

MarchView是视图（View）

ViewWrapper是控制器（Controller）

--------------------------------------------------

想要在Qt程序中通过操作一个3x3的矩阵来控制视图的缩放和移动，然后将这个矩阵传递给一个OpenGL视图进行渲染。这个需求涉及到多个类之间的交互，包括ViewWrapper、Scene和MarchView。
首先，我需要理解ViewWrapper类的结构。它继承自QWidget，并且包含两个成员变量：m_scene和m_glView。m_scene是一个普通的类，用于数据管理，而m_glView是一个用于渲染的OpenGL视图。
接下来，我需要考虑如何在ViewWrapper中处理鼠标事件，以实现视图的缩放和移动。这涉及到重写mousePressEvent、mouseMoveEvent和wheelEvent等事件处理函数。


Scene类。它需要包含一个3x3的矩阵m_matOrtho，用于存储视图的变换信息
