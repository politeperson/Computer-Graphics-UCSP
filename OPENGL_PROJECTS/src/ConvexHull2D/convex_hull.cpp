#include "convex_hull.h"


bool lexical_comp(Point a, Point b)
{
	if (fabs(a.x - b.x) < EPS)
		return a.y < b.y;
	return a.x < b.x;
}
// genera un random float entre [a,b]
float random(float a, float b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}

// GRAHAM SCAN
// true if turn left false otherwise
// a: tercer último, b: segundo último, c: último
bool turned_left(Point a, Point b, Point c)
{
	float first_pend = (b.y - a.y) / (b.x - a.x), second_pend = (c.y - b.y) / (c.x - b.x);
	return first_pend < 0 && second_pend >= 0;
}

// true if turn right false otherwise
// a: tercer último, b: segundo último, c: último
bool turned_right(Point a, Point b, Point c)
{
    float first_pend = (b.y - a.y) / (b.x - a.x), second_pend = (c.y - b.y) / (c.x - b.x);
    return first_pend >= 0 && second_pend < 0;
}

std::vector<Point> UpperConvexHull(std::vector<Point> S)
{
    std::vector<Point> L;
    L.insert(L.begin(), { S[0], S[1] });
    for (int i = 2; i < S.size(); ++i)
    {
        L.push_back(S[i]);
        int k = L.size();
        while (k > 2 && turned_left(L[k * 1u - 3], L[k * 1u - 2], L[k * 1u - 1])) {
            L.erase(L.end() - 2); // eliminando el segundo último
            k = L.size();
        }
    }
    return L;
}

std::vector<Point> LowerConvexHull(std::vector<Point> S)
{
    std::vector<Point> L;
    L.insert(L.begin(), { S[0], S[1] });
    for (int i = 2; i < S.size(); ++i)
    {
        L.push_back(S[i]);
        int k = L.size();
        while (k > 2 && turned_right(L[k * 1u - 3], L[k * 1u - 2], L[k * 1u - 1])) {
            L.erase(L.end() - 2); // eliminando el segundo último
            k = L.size();
        }
    }
    return L;
}

std::vector<Point> GrahamScan(std::vector<Point> S, int& uconv_size, int& lconv_size)
{
    // first sort lexicographically
    std::sort(S.begin(), S.end(), lexical_comp); // nlog(n)
    std::vector<Point> conv_hull;

    std::vector<Point> upper_conv = UpperConvexHull(S);
    conv_hull.insert(conv_hull.end(), upper_conv.begin(), upper_conv.end());
    std::vector<Point> lower_conv = LowerConvexHull(S);
    std::reverse(lower_conv.begin(), lower_conv.end()); // reverse to follow a path
    conv_hull.insert(conv_hull.end(), lower_conv.begin(), lower_conv.end());


    uconv_size = upper_conv.size();
    lconv_size = lower_conv.size();
    
    return conv_hull;
}