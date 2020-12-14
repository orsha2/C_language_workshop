public class Main
{
    private static final double EPSILON = 0.001;

        // Note: This method is NOT the same method as the almostEquals method of class ComplexNumber.
        private static boolean almostEquals(double f1, double f2)
        {
                return Math.abs(f1 - f2) < EPSILON;
        }

        public static void main(String argv[])
        {
                ComplexNumber z1 = new ComplexNumber(1, 2);
                ComplexNumber z2 = new ComplexNumber(3, 4);
                ComplexNumber z3 = new ComplexNumber(1, 1);
                
		ComplexNumber plusResult = z1.plus(z2);


                assert plusResult.almostEquals(new ComplexNumber(4, 6));
                assert almostEquals(plusResult.getImaginaryPart(), 6);

                assert z1.minus(z2).almostEquals(new ComplexNumber(-2, -2));
                assert almostEquals(z1.minus(z2).getRealPart(), -2);

                assert almostEquals(z1.times(z2).getRadius(), z1.getRadius() * z2.getRadius());
                assert almostEquals(z1.times(z2).getArgument(), z1.getArgument() + z2.getArgument());

                assert almostEquals(z1.divide(z2).getRadius(), z1.getRadius() / z2.getRadius());
                assert almostEquals(z1.divide(z2).getArgument(), z1.getArgument() - z2.getArgument());

                assert almostEquals(z1.getImaginaryPart(), 2);
		assert almostEquals(z2.getRealPart(), 3);
		assert almostEquals(z2.getRadius(), 5); 	 
		assert almostEquals(z3.getArgument(), 0.7854); 
		

	        plusResult = z1.plus(z3);
                assert plusResult.almostEquals(new ComplexNumber(2, 3));
		assert almostEquals(plusResult.getImaginaryPart(), 3);

		assert z1.minus(z3).almostEquals(new ComplexNumber(0, 1));
		assert almostEquals(z1.minus(z3).getRealPart(), 0);

                assert almostEquals(z1.times(z3).getRadius(), z1.getRadius() * z3.getRadius());
		assert almostEquals(z1.times(z3).getArgument(), z1.getArgument() + z3.getArgument());

                assert almostEquals(z1.divide(z3).getRadius(), z1.getRadius() / z3.getRadius());
         	assert almostEquals(z1.divide(z3).getArgument(), z1.getArgument() - z3.getArgument());



















          
                

        }
}
