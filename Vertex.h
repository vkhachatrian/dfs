#ifndef VERTEX_H
#define VERTEX_H

enum class Color
{
    White,
    Gray,
    Black
};

struct Vertex
{
    explicit Vertex(int number, Color color = Color::White)
        : number{number},
          discoveryTime{0},
          finishTime{0},
          color(color),
          predecessor(nullptr)
    {}

    bool operator==(const Vertex &other) const
    {
        return number == other.number;
    }

    int number;
    int discoveryTime;
    int finishTime;
    Color color;
    Vertex *predecessor;
};

struct VertexHash
{
    std::size_t operator()(const std::shared_ptr<Vertex> &v) const
    {
        return std::hash<int>()(v->number);
    }
};

struct VertexEqual
{
    bool operator()(const std::shared_ptr<Vertex> &lhs, const std::shared_ptr<Vertex> &rhs) const
    {
        return lhs->number == rhs->number;
    }
};

#endif // VERTEX_H