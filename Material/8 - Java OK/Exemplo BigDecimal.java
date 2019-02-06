//Código errado retornando o Exception
  import java.math.BigDecimal;
   
  public class MyAppBigDecimal {
   
         /**
          * @param args
          */
         public static void main(String[] args) {
               
               System.out.println("Divide");
               System.out.println(new BigDecimal("1.00").divide(new BigDecimal("1.3")));
   
   
         }
   
  }
  Saída:
  Divide
  Exception in thread "main" java.lang.ArithmeticException: Non-terminating decimal expansion; no exact representable decimal result.
         at java.math.BigDecimal.divide(BigDecimal.java:1603)
         at MyAppBigDecimal.main(MyAppBigDecimal.java:11)
   
   
   
  //Código Correto retornando valor arredondado
  import java.math.BigDecimal;
  import java.math.RoundingMode;
   
  public class MyAppBigDecimal {
   
         /**
          * @param args
          */
         public static void main(String[] args) {
               
               System.out.println("Divide");
               System.out.println(new BigDecimal("1.00").divide(new BigDecimal("1.3"),3,RoundingMode.UP));
   
   
         }
   
  }
  Saída:
  Divide
  0.770


CEILING
Rounding mode to round towards positive infinity.
DOWN
Rounding mode to round towards zero.
FLOOR
Rounding mode to round towards negative infinity.
HALF_DOWN
Rounding mode to round towards "nearest neighbor" unless both neighbors are equidistant, in which case round down.
HALF_EVEN
Rounding mode to round towards the "nearest neighbor" unless both neighbors are equidistant, in which case, round towards the even neighbor.
HALF_UP
Rounding mode to round towards "nearest neighbor" unless both neighbors are equidistant, in which case round up.
UNNECESSARY
Rounding mode to assert that the requested operation has an exact result, hence no rounding is necessary.
UP
Rounding mode to round away from zero.

