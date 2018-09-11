package test_package;

public class TestClass {
  public static void main(String[] args) {
    new TestClass().helloWorld();
  }

  protected void helloWorld() {
    System.out.println("Hello world, from " + getClass().getName());
  }
}

