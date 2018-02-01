package as;

import java.util.Map.Entry;

public class Bytecode {
	public static final byte
		NOP = 0,
		MOV = 1,
		ADD = 2,
		SUB = 3,
		MUL = 4,
		DIV = 5,
		MOD = 6,
		AND = 7,
		OR = 8,
		XOR = 9,
		NEG = 10,
		NOT = 11,
		PUSH = 12,
		POP = 13,
		PEEK = 14,
		RSHF = 15,
		LSHF = 16,
		PRINT = 17,
		READ = 18,
		INC = 19,
		DEC = 20,
		JMP = 21,
		HLT = 22,
		EXIT = 23,
		COPY = 24,
		FILL = 25,
		CALL = 26,
		RET = 27,
		XCHG = 28,
		CMP = 29,
		CMPS = 30,
		JE = 31,
		JNE = 32,
		JG = 33,
		JGE = 34,
		JL = 35,
		JLE = 36,
		LOOP = 37,
		IMUL = 38,
		IDIV = 39,
		SLEEP = 40,
		
		TYPE_REG = 0,
		TYPE_REF = 1,
		TYPE_INT = 2,
		
		REG_A = 0,
		REG_B = 1,
		REG_C = 2,
		REG_D = 3,
		REG_SI = 4,
		REG_DI = 5,
		REG_SP = 6,
		REG_IP = 7,
		REG_FLAGS = 8;
	public static byte getType(String v) {
		for(Entry<String, Entry<Integer, Byte>> e : Assembler.replaces.entrySet()) {
			if(v.equals(e.getKey())) {
				return e.getValue().getValue();
			}
		}
		if(v.startsWith("%"))return TYPE_REG;
		if(v.startsWith("[") && v.endsWith("]")) return TYPE_REF;
		if(v.startsWith("$") || (v.startsWith("'") && v.endsWith("'")))return TYPE_INT;
		return -1;
	}
	public static int getValue(String v) {
		for(Entry<String, Entry<Integer, Byte>> e : Assembler.replaces.entrySet()) {
			if(v.equals(e.getKey())) {
				return e.getValue().getKey() & 0xFF;
			}
		}
		byte type = getType(v);
		switch(type) {
		case TYPE_REG: {
			String reg = v.substring(1);
			if(reg.equalsIgnoreCase("a")) return REG_A;
			if(reg.equalsIgnoreCase("b")) return REG_B;
			if(reg.equalsIgnoreCase("c")) return REG_C;
			if(reg.equalsIgnoreCase("d")) return REG_D;
			if(reg.equalsIgnoreCase("si")) return REG_SI;
			if(reg.equalsIgnoreCase("di")) return REG_DI;
			if(reg.equalsIgnoreCase("sp")) return REG_SP;
			return -2;
		}
		case TYPE_REF: {
			return parseByte(v.substring(1, v.indexOf(']')));
		}
		case TYPE_INT: {
			if(v.startsWith("'") && v.endsWith("'")) return parseByte(v);
			return parseByte(v.substring(1));
		}
		default: return -3;
		}
	}
	public static int parseByte(String str) {
		int i;
		try {
			if(str.startsWith("0x")) i = Integer.parseUnsignedInt(str.substring(2), 16);
			else if(str.startsWith("0b")) i = Integer.parseInt(str.substring(2), 2);
			else if(str.charAt(0) == '\'' && str.charAt(2) == '\'') i = str.charAt(1);
			else i = Integer.parseUnsignedInt(str, 10);
		} catch (NumberFormatException e) {
			return -3;
		}
		if(i > 255) return -1;
		else if(i < 0) return -2;
		else return i;		
	}
	public static byte toByte(int i) {
		return (byte) (i);
	}
}
