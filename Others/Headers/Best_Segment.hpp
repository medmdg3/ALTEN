#pragma once
#include"Best_Circle.hpp"
#include"Best_Circle.cpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
/// @brief Introducing Segment as a new struct, it is defined by two edges a and b
struct Segment{
    pair<ld,ld> a=mk(0,0),b=mk(0,1);
};
/// @brief Calculate the scalar product of two given vectors
/// @param A the first given vector
/// @param B the second given vector
/// @return the calculated value
ld prod_Scalaire(pair<ld,ld> A,pair<ld,ld> B);
/// @brief Calculate the distance between a given point and a given segment
/// @param pt the given point
/// @param s the given segment
/// @return the value described above
ld get_Distance(pair<ld,ld>  pt, Segment s);
/// @brief Calculate the angle of inclinaison of a given segment
/// @param A the given segment
/// @return the calculated value
ld get_angle(Segment A);
/// @brief Find the pair a and b that correspond to the line equation "Y=aX+b" in which a given segment is included   (\f$ a= 10^18 \f$ in case the line is verticle)
/// @param A the given segment
/// @return The pair described above
pair<ld,ld> get_line(Segment A);
/// @brief Find the coordonates of the intersection of two lines (caracterised by a segment), or return the pair \f$ (-10^18 ,10^18 ) \f$ if there isn't exactly one
/// @param A the segment caracterising the first line
/// @param B the segment caracterising the second line
/// @return the pair described above
pair<ld,ld> Seg_intersection(Segment A, Segment B);
/// @brief calculate the angle between the horizontal line and the tangent to a directed circle in a  given point
/// @param C The circle described above
/// @param A the given point
/// @param A1 A point where the angle is well know
/// @param ang1 the value of the angle in this point
/// @return the value described above
ld Angle_from_Circle(Circle C,pair<ld,ld> A,pair<ld,ld> A1,ld ang1);
/// @brief Find the only circle that went through two given points, such that the the angle between the horizontal line and the tangent that circle in a the first point is defined (segments are approximed with a circle with a big radius ~ \f$ 10^9 \f$ )
/// @param angle the given angle
/// @param A the first point
/// @param B the second point
/// @return the circle described above
Circle Circle_from_Angle(ld angle,pair<ld,ld> A,pair<ld,ld> B);
/// @brief Find the maximum distance between a given set of points and a given Segment
/// @param C The given Segment
/// @param P the given set of points
/// @return the value described above
ld Maximum_Unfitness(Segment C,vector<pair<ld,ld> > P);
/// @brief Customisable. \n Calculate the unfitness between a given set of points along with and a given arc of a circle 
/// @param C the given circle
/// @param angle1 the angle describing the start of the arc
/// @param angle2 the angle describing the end of the arc
/// @param P the given set of points
/// @return the value described above
ld Arc_unfitness(Circle C,ld angle1,ld angle2,vector<pair<ld,ld> > P);
/// @brief  Customisable. \n Calculate the maximum error between a given set of points along with and a given arc of a circle 
/// @param C the given circle
/// @param angle1 the angle describing the start of the arc
/// @param angle2 the angle describing the end of the arc
/// @param P the given set of points
/// @return the value described above
ld Max_Arc_unfitness(Circle C,ld angle1,ld angle2,vector<pair<ld,ld> > P);
/// @brief Calculate the average distance squared between a given set of points and a given Segment
/// @param C the given circle
/// @param P the given set of points
/// @return the value described above
ld Segment_unfitness(Segment C,vector<pair<ld,ld> > P);