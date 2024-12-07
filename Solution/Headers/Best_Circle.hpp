#pragma once
#include<bits/stdc++.h>
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
/// @brief Introducing circles as a new struct, they are determined with a center O and a radius r
struct Circle{
    pair<ld,ld> O;
    ld r;
};
/// @brief find the distance between two given points squared
/// @param P1 the first point
/// @param P2 the second point
/// @return the distance described above
ld distance_square(pair<ld,ld> P1,pair<ld,ld> P2);
/// @brief Find the maximum distance between a given set of points and a given cercle
/// @param C The given circle
/// @param P the given set of points
/// @return the value described above
ld Maximum_Unfitness(Circle C,vector<pair<ld,ld> > P);
/// @brief Calculate the average distance squared between a given set of points and a given circle
/// @param C the given circle
/// @param P the given set of points
/// @return the value described above
ld Circle_unfitness(Circle C,vector<pair<ld,ld> > P);
/// @brief return the norm of a given vector
/// @param vect the vector described above
/// @return the value described above
ld norm(pair<ld,ld> vect);
/// @brief Find a vector with norm equal to 1 who is perpendicular to a segment
/// @param P1 first born of the described segment
/// @param P2 second born of the described segment
/// @return the vector described above
pair<ld,ld> get_verticle(pair<ld,ld> P1,pair<ld,ld> P2);
/// @brief Find a center for a circle with a given radius  and went through two given points
/// @param P1 The first given point
/// @param P2 The second given point
/// @param r The given radius
/// @param Down You can change the value from false to true in order to change the center (It can be proven there is at most two different centers)
/// @return The center described above
pair<ld,ld> best_center(pair<ld,ld> P1,pair<ld,ld> P2,ld r,bool Down=false);