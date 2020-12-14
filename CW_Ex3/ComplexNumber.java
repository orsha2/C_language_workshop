import java.lang.Math;

public class ComplexNumber {
    private static final double EPSILON = 0.001;
    private final double realPart;
    private final double imaginaryPart;

    public ComplexNumber(double real, double imaginary) {
        this.realPart = real;
        this.imaginaryPart = imaginary;
    }

    public double getRealPart() {
        return this.realPart;
    }

    public double getImaginaryPart() {
        return this.imaginaryPart;
    }

    public double getRadius() {
        return this.getDistance(0, 0);
    }

    public double getArgument() {
        return Math.atan2(this.imaginaryPart, this.realPart);
    }

    public ComplexNumber plus(ComplexNumber other) {
        double real = this.realPart + other.realPart;
        double imginary = this.imaginaryPart + other.imaginaryPart;

        return new ComplexNumber(real, imginary);
    }

    public ComplexNumber minus(ComplexNumber other) {
        double real = this.realPart - other.realPart;
        double imginary = this.imaginaryPart - other.imaginaryPart;

        return new ComplexNumber(real, imginary);
    }

    public ComplexNumber times(ComplexNumber other) {
        double real = this.realPart * other.realPart - this.imaginaryPart * other.imaginaryPart;
        double imginary = this.realPart * other.imaginaryPart + this.imaginaryPart * other.realPart;

        return new ComplexNumber(real, imginary);
    }

    public ComplexNumber divide(ComplexNumber other) {
        return this.times(other.getInverse());
    }

    public boolean almostEquals(ComplexNumber other) {
        return (this.getDistance(other.realPart, other.imaginaryPart) < EPSILON);
    }

    static public ComplexNumber fromPolarCoordinates(double radius, double argument) {
        double real = radius * Math.cos(argument);
        double imaginary = radius * Math.sin(argument);

        return new ComplexNumber(real, imaginary);
    }

    private ComplexNumber getInverse() {
        return ComplexNumber.fromPolarCoordinates(1 /  this.getRadius(), -this.getArgument());
    }

    private double getDistance(double real, double imaginary) {
        double realPartDiff = this.realPart - real;
        double imaginaryPartDiff = this.imaginaryPart - imaginary;

        double distance = Math.sqrt(realPartDiff * realPartDiff + imaginaryPartDiff * imaginaryPartDiff);
        return distance;
    }
}
