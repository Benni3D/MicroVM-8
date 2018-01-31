package as;

import static as.Bytecode.*;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.MalformedInputException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class Assembler {
	private int bytes;
	public int assemble(File in, File bin) {
		try {
			List<String> lines = Files.readAllLines(in.toPath(), Charset.forName("utf-8"));
			DataOutputStream out = new DataOutputStream(new FileOutputStream(bin));
			
			for(String line : lines) {
				byte[] bytes = asm(line);
				if(bytes != null) {
					out.writeBytes(new String(bytes));
					this.bytes += bytes.length;
				}
			}
			
			out.close();
			return 0;
		} catch (MalformedInputException ex) {
			System.err.println("Only UTF-8 is supported!");
			return -255;
		} catch (IOException e) {
			System.err.println("Can't open " + in.getName() + "!");
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}
	public byte[] asm(String line) {
		if(line.startsWith(";") || line.isEmpty()) return null;
		if(line.toLowerCase().startsWith("nop")) return new byte[] { NOP };
		if(line.toLowerCase().startsWith("mov ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				MOV, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("add ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				ADD, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("sub ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				SUB, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("mul ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				MUL, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("div ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				DIV, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("mod ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				MOD, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("and ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				AND, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)	
			};
		}
		if(line.toLowerCase().startsWith("or ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				OR, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("xor ")) {
			String param1 = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			String param2 = line.substring(line.indexOf(',')+1).trim();
			byte pt1 = getType(param1);
			byte pt2 = getType(param2);
			if(pt1 == -1 || pt2 == -1) {
				System.err.println("Invalid Instruction Types!");
				return null;
			}
			int value1 = getValue(param1);
			int value2 = getValue(param2);
			if(value1 < 0 || value2 < 0 || value1 > 255 || value2 > 255) {
				System.err.println("Invalid Values!");
				return null;
			}
			return new byte[] {
				XOR, (byte) ((pt1 << 4) | pt2), toByte(value1), toByte(value2)
			};
		}
		if(line.toLowerCase().startsWith("neg ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					NEG, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("not ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					NOT, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("push ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					PUSH, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("pop ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					POP, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("rshf ")) {
			String param = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			int bytes = parseByte(line.substring(line.indexOf(',')+1).trim().substring(1));
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					RSHF, (byte) pt, toByte(value), (byte) bytes
			};
		}
		if(line.toLowerCase().startsWith("lshf ")) {
			String param = line.substring(line.indexOf(' ')+1, line.indexOf(',')).trim();
			int bytes = parseByte(line.substring(line.indexOf(',')+1).trim().substring(1));
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					LSHF, (byte) pt, toByte(value), (byte) bytes
			};
		}
		if(line.toLowerCase().startsWith("printi ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					PRINT, (byte) (pt), toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("printc ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					PRINT, (byte) ((1 << 4) | pt), toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("prints ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt != TYPE_REF) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
				PRINT, (byte) ((2 << 4) | pt), toByte(value)	
			};
		}
		if(line.toLowerCase().startsWith("readi ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					READ, pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("readc ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					READ, (byte) ((1 << 4) | pt), toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("reads ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt != TYPE_REF) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
				READ, (byte) ((2 << 4) | pt), toByte(value)	
			};
		}
		if(line.toLowerCase().startsWith("inc ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					INC, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("dec ")) {
			String param = line.substring(line.indexOf(' ')).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
					DEC, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("jmp ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt == -1) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			return new byte[] {
				JMP, (byte) pt, toByte(value)
			};
		}
		if(line.toLowerCase().startsWith("hlt")) return new byte[] { HLT };
		if(line.toLowerCase().startsWith("exit")) return new byte[] { EXIT };
		if(line.toLowerCase().startsWith(".def ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			String[] pvalues = param.split(",");
			List<Byte> bytes = new ArrayList<>();
			for(String v : pvalues) {
				v = v.trim();
				if((v.startsWith("\"") && v.endsWith("\"")) || (v.startsWith("'") && v.endsWith("'"))) {
					v = v.substring(1, v.length() - 1);
					byte[] vb = v.getBytes();
					for(byte b : vb) bytes.add(b);
				} else if(v.startsWith("$")) {
					v = v.substring(1);
					bytes.add(toByte(parseByte(v)));
				}
			}
			Byte[] uBytes = bytes.toArray(new Byte[bytes.size()]);
			byte[] rBytes = new byte[uBytes.length];
			for(int i = 0; i < uBytes.length; i++) rBytes[i] = uBytes[i].byteValue();
			return rBytes;
		}
		if(line.toLowerCase().startsWith(".space ")) {
			String param = line.substring(line.indexOf(' ')+1).trim();
			byte pt = getType(param);
			if(pt != TYPE_INT) {
				System.err.println("Invalid Instruction Type! line=" + line);
				return null;
			}
			int value = getValue(param);
			if(value < 0 || value > 255) {
				System.err.println("Invalid Value! " + value);
				return null;
			}
			int space = value - bytes;
			if(space < 0) space = 0;
			byte[] bytes = new byte[space];
			for(int i = 0; i < bytes.length; i++) bytes[i] = 0;
			return bytes;
		}
		
		System.err.println("Unknown Instruction \"" + line + "\"");
		return null;
	}
}
