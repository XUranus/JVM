import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.io.FileReader;

public class FileTest {
  public static void main(String[] args) throws Exception {
    System.out.println("ready to write file");
    FileWriter writer = new FileWriter("out");
    writer.write("============== Hello World ===========\n");
    writer.write("this is a line to be written into file\n");
    writer.write("======================================\n");
    writer.close();
    System.out.println("write Done");
    System.out.println("ready to read file");
    BufferedReader reader = new BufferedReader(new FileReader("out"));
    String line;
    while((line = reader.readLine()) != null) {
      System.out.println(line);
    }
    System.out.println("read Done");
  }
}