import java.io.File;

import as.Assembler;

public class Main {
	private static boolean _DEBUG = false;
	public static void main(String[] args) {
		String src, bin;
		if(_DEBUG) {
			src = "code.txt";
			bin = "prog.bin";
		} else {
			if(args.length != 2) {
				System.err.println("Usage: microasm8 <src> <bin>");
				return;
			}
			src = args[0];
			bin = args[1];
		}
		int i = Assembler.assemble(new File(src), new File(bin));
		if(i == 0)
			System.out.println("\nAssembling complete without errors!");
		else System.err.println("\nAssembling interrupted by an error!");
	}
}
