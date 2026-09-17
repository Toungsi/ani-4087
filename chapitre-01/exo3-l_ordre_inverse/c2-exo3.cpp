#include <iostream>
#include <iomanip>

struct Vec3 {
    double x, y, z;
};

struct Quat {
    double w, x, y, z; // quaternion w,x,y,z — supposé déjà normalisé
};

struct Pose {
    Vec3 position;
    Quat rotation;
};

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 tourner(const Quat& q, const Vec3& v) {
    Vec3 qv{q.x, q.y, q.z};

    Vec3 t{
        2.0 * (qv.y * v.z - qv.z * v.y),
        2.0 * (qv.z * v.x - qv.x * v.z),
        2.0 * (qv.x * v.y - qv.y * v.x)
    };

    Vec3 qv_x_t{
        qv.y * t.z - qv.z * t.y,
        qv.z * t.x - qv.x * t.z,
        qv.x * t.y - qv.y * t.x
    };

    return Vec3{
        v.x + q.w * t.x + qv_x_t.x,
        v.y + q.w * t.y + qv_x_t.y,
        v.z + q.w * t.z + qv_x_t.z
    };
}

// Rotation puis translation.
Vec3 appliquerRT(const Pose& pose, const Vec3& point) {
    return tourner(pose.rotation, point) + pose.position;
}

// Translation puis rotation.
Vec3 appliquerTR(const Pose& pose, const Vec3& point) {
    return tourner(pose.rotation, point + pose.position);
}

int main() {
    Pose pose;

    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;
    std::cin >> pose.rotation.w >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z;

    Vec3 point;
    std::cin >> point.x >> point.y >> point.z;

    Vec3 resultatRT = appliquerRT(pose, point);
    Vec3 resultatTR = appliquerTR(pose, point);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << resultatRT.x << " " << resultatRT.y << " " << resultatRT.z << "\n";
    std::cout << resultatTR.x << " " << resultatTR.y << " " << resultatTR.z << "\n";

    return 0;
}