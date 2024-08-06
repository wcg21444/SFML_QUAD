#include "Quadtree.h"
#include "Object.h"
#include "Base.h"
DivsionOutline::DivsionOutline(float radius, sf::Vector2f center, sf::Color color)
{
	shape = sf::RectangleShape(sf::Vector2f(2 * radius, 2 * radius));
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(center);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(1);
}

DivsionOutline::DivsionOutline(sf::Rect<float> rect, sf::Color color)
{
    shape = sf::RectangleShape(rect.getSize());
    shape.setOrigin(rect.getSize() / 2);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(rect.getPosition()+rect.getSize()/2);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1);
}

void DivsionOutline::draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
}

//传入新节点的参数
QuadtreeNode::QuadtreeNode(QuadtreeNode* parent_, std::vector<Object*> objects_, sf::Rect<float> div_area_, int depth_, const Quadtree* tree_)
    :parent(parent_), curr_depth(depth_),div_area(div_area_)
{
    for (int i = 0; i < 4; ++i)
    {
        children[i] = nullptr;//初始化子节点
    }
    sf::Color color(255.f, 100.f + curr_depth * 60.f, curr_depth * 60.f);
    div_outline = DivsionOutline(div_area, color);

    if (objects_.size() > tree_->max_node_objects && curr_depth < tree_->max_depth)//节点满足继续划分条件
    {
        std::vector<Object*> sub_objs[4];
        sf::Rect<float> sub_area[4];

        sub_area[0] = sf::Rect<float>(div_area.getPosition(), 
            div_area.getSize() / 2);
        sub_area[1] = sf::Rect<float>(div_area.getPosition()+sf::Vector2f(div_area.getSize().x/2,0.f),
            div_area.getSize() / 2);
        sub_area[2] = sf::Rect<float>(div_area.getPosition()+ sf::Vector2f(div_area.getSize().x / 2,div_area.getSize().y / 2), 
            div_area.getSize() / 2);
        sub_area[3] = sf::Rect<float>(div_area.getPosition()+ sf::Vector2f(0.f, div_area.getSize().y / 2),
            div_area.getSize() / 2);

        for (Object* p_obj : objects_)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (sub_area[i].intersects(p_obj->bound_box))
                {
                    sub_objs[i].push_back(p_obj);
                }
            }
        }

        for (int i = 0; i < 4; ++i)
        {
            children[i] = new QuadtreeNode(this, sub_objs[i], sub_area[i], curr_depth + 1, tree_);
        }
    }
    else
    {
        this->objects = objects_;
    }

}

bool QuadtreeNode::isLeaveNode()
{
	for (int i = 0; i < 4; ++i)
	{
		if (children[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}

void QuadtreeNode::draw(sf::RenderWindow& wnd)
{
    div_outline.draw(wnd);
}

Quadtree::Quadtree(std::vector<Object*> objects_, int max_depth_, int max_num_, sf::Rect<float> worldspace_)
	:max_depth(max_depth_), max_node_objects(max_num_),depth(1),worldspace(worldspace_)
{
    root = new QuadtreeNode(nullptr, objects_, worldspace_,1,this);
}

void Quadtree::travelRecursion(QuadtreeNode* curr_node, std::function<void(QuadtreeNode*)> operation)
{
    operation(curr_node);
    for (int i = 0; i < 4; ++i)
    {
        if (curr_node->children[i] != nullptr)
        {
            travelRecursion(curr_node->children[i], operation);
        }
    }
    if (curr_node->isLeaveNode())
    {

        return;
    }
}

void Quadtree::travel(std::function<void(QuadtreeNode*)> operation)
{
    travelRecursion(root, operation);
}

void Quadtree::draw(sf::RenderWindow& wnd)
{
    travel([&](QuadtreeNode* node)->void {
        node->draw(wnd);
        });
}
