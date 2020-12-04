import java.lang.Math;

public class ComplexNumber{
    private static final double EPSILON = 0.001;

    double realPart;
    double imaginaryPart;

    public ComplexNumber(double real, double img){
        this.realPart = real;
        this.imaginaryPart = img;  
    }

    public ComplexNumber plus(ComplexNumber other){
        ComplexNumber newComplexNumber = new ComplexNumber ( this.realPart + other.realPart ,
                                                             this.imaginaryPart + other.imaginaryPart); 
        return newComplexNumber; 
    }

    public ComplexNumber minus(ComplexNumber other){
        ComplexNumber newComplexNumber = new ComplexNumber ( this.realPart - other.realPart ,
                                                             this.imaginaryPart - other.imaginaryPart); 
        return newComplexNumber; 
    }

    public ComplexNumber times(ComplexNumber other){
        ComplexNumber newComplexNumber = new ComplexNumber ( this.realPart * other.realPart - 
                                                                    this.imaginaryPart * other.imaginaryPart ,
                                                             this.realPart * other.imaginaryPart + 
                                                                    this.imaginaryPart * other.realPart); 
        return newComplexNumber; 
    }


    public double getRealPart(){
        return this.realPart;
    }

    public double getImaginaryPart(){
        return this.imaginaryPart;
    }

    public double getRadius (){
        return Math.sqrt(this.realPart * this.realPart + this.imaginaryPart*this.imaginaryPart);
    }

    public double getArgument (){
        return Math.atan2(this.realPart , this.imaginaryPart);
    }

    public boolean almostEquals(ComplexNumber other ){
        return this.minus(other).getRadius() < EPSILON;
    }

    public ComplexNumber divide(ComplexNumber other){
        double d = Math.pow(other.getRadius(),2);
        double n1 = this.realPart*other.realPart + this.imaginaryPart*other.imaginaryPart;
        double n2 = this.imaginaryPart*other.realPart - this.realPart*other.imaginaryPart;
        ComplexNumber newComplexNumber = new ComplexNumber(n1/d, n2/d);
        return newComplexNumber;
    }    

}
