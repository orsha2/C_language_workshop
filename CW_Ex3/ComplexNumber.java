import java.lang.Math;

public class ComplexNumber{
    private static final double EPSILON = 0.001;

    private final double realPart;
    private final double imaginaryPart;

    public ComplexNumber(double real, double imginary){
        this.realPart = real;
        this.imaginaryPart = imginary;  
    }

    public ComplexNumber plus(ComplexNumber other){
        double real = this.realPart + other.realPart;
        double imginary = this.imaginaryPart + other.imaginaryPart;
        return new ComplexNumber ( real ,imginary); 
    }

    public ComplexNumber minus(ComplexNumber other){
        double real = this.realPart - other.realPart;
        double imginary = this.imaginaryPart - other.imaginaryPart;
        return new ComplexNumber ( real ,imginary); 
    }

    public ComplexNumber times(ComplexNumber other){
        double real = this.realPart * other.realPart - this.imaginaryPart * other.imaginaryPart;
        double imginary = this.realPart * other.imaginaryPart + this.imaginaryPart * other.realPart;
        return new ComplexNumber ( real ,imginary); 
        
    }

    private ComplexNumber inverse() {
        double radius = this.getRadius();
        return new ComplexNumber(this.realPart / Math.pow(radius,2) ,- this.imaginaryPart / Math.pow(radius,2) );
    }

    public ComplexNumber divide(ComplexNumber other){
        return this.times(other.inverse());
    }    

    public double getRealPart(){
        return this.realPart;
    }

    public double getImaginaryPart(){
        return this.imaginaryPart;
    }

    public double getRadius (){
        return Math.sqrt( Math.pow(this.realPart,2) + Math.pow(this.imaginaryPart,2) );
    }

    public double getArgument (){
        return Math.atan2(this.imaginaryPart, this.realPart);
    }

    public boolean almostEquals(ComplexNumber other ){
        return this.minus(other).getRadius() < EPSILON;
    }


}
