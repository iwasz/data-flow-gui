#include "gui/drawing/MainView.h"
#include "gui/drawing/MainController.h"
#include "gui/drawing/ContainerFactoryStrategy.h"
#include "gui/drawing/ShapeDrawStrategy.h"
#include "gui/drawing/DashedLineStrategy.h"
#include "gui/drawing/DashedLineConnectorStrategy.h"
#include "gui/drawing/RectangularSelectorStrategy.h"
#include "view/Circle.h"
#include "view/Rectangle.h"
#include "view/RectangularSelector.h"
#include "view/Line.h"
#include "view/LineConnector.h"
#include "view/Connector.h"
#include "view/Stage.h"
#include "view/Button.h"
#include "view/CircularNode.h"
#include "primitives/Geometry.h"
#include "view/ScaleLayer.h"
