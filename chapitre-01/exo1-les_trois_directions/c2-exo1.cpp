#include <iostream>
#include <iomanip>

struct Vec3 {
    double x, y, z;
};

double produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// --- Convention fixée une fois pour toutes ---
// Repère direct : X = Avant, Y = Droite, Z = Haut.
Vec3 Avant()  { return Vec3{1.0, 0.0, 0.0}; }
Vec3 Haut()   { return Vec3{0.0, 0.0, 1.0}; }
Vec3 Droite() { return Vec3{0.0, 1.0, 0.0}; }
// ----------------------------------------------

int main() {
    double x, y, z;
    std::cin >> x >> y >> z;

    Vec3 point{x, y, z};

    std::cout << std::fixed << std::setprecision(4);
    std::cout << produitScalaire(point, Avant())  << "\n";
    std::cout << produitScalaire(point, Haut())   << "\n";
    std::cout << produitScalaire(point, Droite()) << "\n";

    return 0;
}