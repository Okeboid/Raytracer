//
// Created by Peter Zdankin on 04.11.24.
//

#include "Vector3.hpp"

#include <ranges>

vec3::vec3() {
    elements[0] = 0;
    elements[1] = 0;
    elements[2] = 0;
}

vec3::vec3(double x, double y, double z) {
    elements[0] = x;
    elements[1] = y;
    elements[2] = z;
}

double vec3::x() const {
    return elements[0];
}

double vec3::y() const {
    return elements[1];
}
double vec3::z() const {
    return elements[2];
}

//returns a vector where each of the elements is flipped from positive to negative and vice versa
vec3 vec3::operator-() const {

    return {-elements[0],-elements[1],-elements[2]};
}

// return the i-th element of the elements vector
double vec3::operator[](int i) const {
 return elements[i]; //not sure
}

// return the i-th element of the element
double& vec3::operator[](int i) {
 return elements[i]; //not sure
}


vec3& vec3::operator+=(const vec3& v) {
    elements[0] += v.elements[0];
    elements[1] += v.elements[1];
    elements[2] += v.elements[2];
    return *this;
}

vec3& vec3::operator*=(double t) {
    elements[0] *= t;
    elements[1] *= t;
    elements[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) {
    elements[0] /= t;
    elements[1] /= t;
    elements[2] /= t;
    return *this;
}

// Return the length of the vector
double vec3::length() const {
    double l=elements[0]*elements[0]+elements[1]*elements[1]+elements[2]*elements[2];
    return sqrt(l);
}

// Return the length but squared
double vec3::length_squared() const {
    double l=elements[0]*elements[0]+elements[1]*elements[1]+elements[2]*elements[2];
    return l;
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.elements[0] << ' ' << v.elements[1] << ' ' << v.elements[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
    return {u.elements[0] + v.elements[0], u.elements[1] + v.elements[1], u.elements[2] + v.elements[2]};
}

vec3 operator-(const vec3& u, const vec3& v) {
    return {u.elements[0] - v.elements[0], u.elements[1] - v.elements[1], u.elements[2] - v.elements[2]};
}

vec3 operator*(const vec3& u, const vec3& v) {
    return {u.elements[0] * v.elements[0], u.elements[1] * v.elements[1], u.elements[2] * v.elements[2]};
}

// To scale a number with a vector
vec3 operator*(double t, const vec3& v){
    return {v.elements[0]*t, v.elements[1]*t, v.elements[2]*t};
}

// To scale a vector with a number
vec3 operator*(const vec3& v, double t){
    return t*v;
}

// To divide a vector by a number
vec3 operator/(const vec3& v, double t) {
    return {v.elements[0]/t, v.elements[1]/t, v.elements[2]/t};
}

// dot product of a vector, i should google what a dot product is
double dot(const vec3& u, const vec3& v) {
    return (v.elements[0]*u.elements[0] + v.elements[1]*u.elements[1] + v.elements[2]*u.elements[2]);
}

// cross product of a vector, i should google what a dot product is
vec3 cross(const vec3& u, const vec3& v) {
    return {u.elements[1]*v.elements[2] - u.elements[2]*v.elements[1],u.elements[2]*v.elements[0] - u.elements[0]*v.elements[2],u.elements[0]*v.elements[1] - u.elements[1]*v.elements[0]};
}

// To normalize a vector such that it has a length of 1, we need to divide a vector by its length
vec3 unit_vector(const vec3& v) {
    double len = v.length();
    if (len == 0) {
        throw std::runtime_error("Cannot normalize a zero-length vector");
    }
    return v / len;
}