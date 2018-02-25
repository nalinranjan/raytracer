#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;

int main(int argc, char const *argv[])
{
    Vector3f a(1,2,3);
    Vector3f b(4,5,6);
    std::cout << a.cwiseProduct(b) << std::endl;
    return 0;
}