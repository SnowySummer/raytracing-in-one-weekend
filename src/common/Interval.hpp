#ifndef COMMON__INTERVAL_HPP
#define COMMON__INTERVAL_HPP

class Interval {
public:
    float min;
    float max;

public:
    // Interval constructor
    Interval() : min(0.0f), max(0.0f) {}
    Interval(float _min, float _max) : min(_min), max(_max) {}

    // Bounds checking
    bool surrounds(float t) { return min <  t && t <  max; }
    bool contains(float t)  { return min <= t && t <= max; }

    // Size
    float size() const { return max - min; }

    // Clamp values
    float clamp(float t) {
        if (t < min) return min;
        if (max < t) return max;
        return t;
    }

    // Expand interval
    Interval expand(float delta) {
        return Interval(min - 0.5f * delta, max + 0.5f * delta);
    }

    // Operator overload
    friend Interval operator+(Interval interval, float t);
};


// Operator overload implementation
inline Interval operator+(Interval interval, float t) {
    return Interval(interval.min + t, interval.max + t);
}

#endif