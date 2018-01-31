import java.io.File;

import as.Assembler;

public class Main {
	public static void main(String[] args) {
		if(args.length != 2) {
			System.err.println("Usage: microasm8 <src> <bin>");
			return;
		}
		new Assembler().assemble(new File(args[0]), new File(args[1]));
	}
}
