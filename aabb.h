#ifndef AABB_H
#define AABB_H

class KdNode;

class AABB
{
public:
    AABB();
    AABB(float, float, float, float, float, float);
    void set(float, float, float, float, float, float);
    void expand(const AABB&);
    bool cmp(const AABB&, int) const;
    void print() const;
    friend KdNode;

private:
    float min[3], max[3];
};

#endif