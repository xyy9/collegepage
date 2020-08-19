#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

//DATAPATH register
struct IF_ID{//stage1-2
    bool input;
    int PC;
    string s;
}if_id;

struct ID_EX{//stage2-3
    bool input;
    int read_data1;
    int read_data2;
    int sign_extend;
    int rs,rt,rd;
    int PC;
    string opcode,func;
    string control_sign;
}id_ex;

struct EX_MEM{//stage3-4
    bool input;
    bool branch,store;
    int ALUout;
    int write_data;
    int rt;//or rd
    int PC;
    string ALU_op;
    string control_sign;
}ex_mem;

struct MEM_WB{//stage4-5
    bool input;
    int read_data;
    int ALUout;
    int rt;//or rd
    string control_sign;
}mem_wb;

void read_file(string,string);
void print_cycle();
void initial();
int bin_dec(string);
bool pipeline();
void Fetch();
void Decode();
void Execute();
void Memory_access();
void Write_back();
void hazard_check();
void Flush();
//
void general();//1
void data_hazard();//2
void lw_hazard();//3
void branch_hazard();//4

//register,memory
int mem[5] = {5,9,4,8,7};
int reg[10] = {0,9,5,7,1,2,3,4,5,6};
//file
ifstream fin;
ofstream fout;
//instruction
string instructions[10];
int clock_cycle = 0;

int main()
{
    general();
    data_hazard();
    lw_hazard();
    branch_hazard();
    return 0;
}

void initial(){
    clock_cycle = 0;
    for(int i = 0;i < 10;i++){
        instructions[i].clear();
    }
    mem[0] = 5;//0x00
    mem[1] = 9;//0x04
    mem[2] = 4;//0x08
    mem[3] = 8;//0x0C
    mem[4] = 7;//0x10
    reg[0] = 0;//$0
    reg[1] = 9;//$1
    reg[2] = 5;//$2
    reg[3] = 7;//$3
    reg[4] = 1;//$4
    reg[5] = 2;//$5
    reg[6] = 3;//$6
    reg[7] = 4;//$7
    reg[8] = 5;//$8
    reg[9] = 6;//$9
    //IF_ID
    if_id.input = false;
    if_id.PC = 0;
    if_id.s = "00000000000000000000000000000000";
    //ID_EX
    id_ex.input = false;
    id_ex.read_data1 = id_ex.read_data2 = 0;
    id_ex.sign_extend = 0;
    id_ex.rs = id_ex.rt = id_ex.rd = 0;
    id_ex.PC = 0;
    id_ex.control_sign = "000000000";
    //EX_MEM
    ex_mem.input = ex_mem.branch = ex_mem.store = false;
    ex_mem.ALUout = 0;
    ex_mem.write_data = 0;
    ex_mem.rt = 0;
    ex_mem.PC = 0;
    ex_mem.control_sign = "00000";
    //MEM_WB
    mem_wb.input = false;
    mem_wb.read_data = 0;
    mem_wb.ALUout = 0;
    mem_wb.rt = 0;
    mem_wb.control_sign = "00";
}

void read_file(string read_name,string output_name){
    fin.open(read_name.c_str());
    fout.open(output_name.c_str());
    string s;
    fin >> s;
    int n = 1,i = 0;
    while(i < s.length()){
        instructions[n] = s.substr(i,32);
        n++;
        i += 32;
    }
    while(pipeline());
    fin.close();
    fout.close();
}

//1-cycle
bool pipeline(){
    Write_back();//row-i
    Memory_access();//row-i+1
    Execute();//row-i+2
    Decode();//row-i+3
    Fetch();//row-i+4
    hazard_check();
    clock_cycle++;
    print_cycle();
    if((mem_wb.control_sign == "00" && mem_wb.ALUout == 0 && mem_wb.read_data == 0)
        && ex_mem.control_sign == "00000" && id_ex.control_sign == "000000000" && clock_cycle != 1){
        return false;
    }
    else{
        return true;
    }
}

void print_cycle(){
    fout<<"CC "<<clock_cycle<<":"<<endl;
    fout<<endl;
    fout<<"Registers:"<<endl;
    fout<<"$0: "<<reg[0]<<endl;
    fout<<"$1: "<<reg[1]<<endl;
    fout<<"$2: "<<reg[2]<<endl;
    fout<<"$3: "<<reg[3]<<endl;
    fout<<"$4: "<<reg[4]<<endl;
    fout<<"$5: "<<reg[5]<<endl;
    fout<<"$6: "<<reg[6]<<endl;
    fout<<"$7: "<<reg[7]<<endl;
    fout<<"$8: "<<reg[8]<<endl;
    fout<<"$9: "<<reg[9]<<endl;
    fout<<endl;
    fout<<"Data memory:"<<endl;
    fout<<"0x00: "<<mem[0]<<endl;
    fout<<"0x04: "<<mem[1]<<endl;
    fout<<"0x08: "<<mem[2]<<endl;
    fout<<"0x0C: "<<mem[3]<<endl;
    fout<<"0x10: "<<mem[4]<<endl;
    fout<<endl;
    fout<<"IF/ID:"<<endl;
    fout<<"PC              "<<if_id.PC<<endl;
    fout<<"Instruction     "<<if_id.s<<endl;
    fout<<endl;
    fout<<"ID/EX :"<<endl;
    fout<<"ReadData1       "<<id_ex.read_data1<<endl;
    fout<<"ReadData2       "<<id_ex.read_data2<<endl;
    fout<<"sign_ext        "<<id_ex.sign_extend<<endl;
    fout<<"Rs              "<<id_ex.rs<<endl;
    fout<<"Rt              "<<id_ex.rt<<endl;
    fout<<"Rd              "<<id_ex.rd<<endl;
    fout<<"Control signals "<<id_ex.control_sign<<endl;
    fout<<endl;
    fout<<"EX/MEM :"<<endl;
    fout<<"ALUout          "<<ex_mem.ALUout<<endl;
    fout<<"WriteData       "<<ex_mem.write_data<<endl;
    fout<<"Rt/Rd           "<<ex_mem.rt<<endl;
    fout<<"Control signals "<<ex_mem.control_sign<<endl;
    fout<<endl;
    fout<<"MEM/WB :"<<endl;
    fout<<"ReadData        "<<mem_wb.read_data<<endl;
    fout<<"ALUout          "<<mem_wb.ALUout<<endl;
    fout<<"Rt/Rd           "<<mem_wb.rt<<endl;
    fout<<"Control signals "<<mem_wb.control_sign<<endl;
    fout<<"================================================="<<endl;
}

//stage1:fetch
void Fetch(){
    if_id.PC += 4;
    if(instructions[if_id.PC/4] == ""){
        if_id.s = "00000000000000000000000000000000";
    }
    else{
        if_id.s = instructions[if_id.PC/4];
    }
    if_id.input = true;
}

//stage2:decode
void Decode(){
    //r-instruction=opcode(6)rs(5)rt(5)rd(5)shift(5)func(6)
    id_ex.opcode = if_id.s.substr(0,6);
    id_ex.input = if_id.input;
    if_id.input = false;
    id_ex.func = if_id.s.substr(26,6);
    id_ex.rs = bin_dec(if_id.s.substr(6,5));
    id_ex.rt = bin_dec(if_id.s.substr(11, 5));
    id_ex.sign_extend = bin_dec(if_id.s.substr(16,16));
    id_ex.read_data1 = reg[id_ex.rs];
    id_ex.read_data2 = reg[id_ex.rt];
    id_ex.PC = if_id.PC;
    //control_sign = [RegDst ALUop1 ALUop0 ALUSrc Branch MemRead MemWrite Regwrite MemtoReg]
    if(id_ex.opcode == "000000"){//R-type
        id_ex.rd = bin_dec(if_id.s.substr(16,5));
        if(id_ex.func == "000000" && id_ex.rs == 0 && id_ex.rt == 0){//nop
            id_ex.control_sign = "000000000";
        }
        else{
            id_ex.control_sign = "110000010";
        }
    }
    else{//I-type
        id_ex.rd = 0;
        if(if_id.s[16] == '1'){
            id_ex.sign_extend = - id_ex.sign_extend;
        }
        //I-instruction find
        if(id_ex.opcode == "100011"){//lw rt,immediate(rs)
            id_ex.control_sign = "000101011";
        }
        else if(id_ex.opcode == "101011"){//sw rt,immediate(rs)
            id_ex.control_sign = "000100100";
        }
        else if(id_ex.opcode == "001000"){//addi rt,rs,immediate
            id_ex.control_sign = "000100010";
        }
        else if(id_ex.opcode == "001100"){//andi rt,rs,immediate
            id_ex.control_sign = "010100010";
        }
        else if(id_ex.opcode == "000100"){//beq rs,rt,label
            id_ex.control_sign = "001010000";
        }
    }
}

//stage3:execute
void Execute(){
    int tmp1,tmp2;
    ex_mem.input = id_ex.input;
    id_ex.input = false;
    ex_mem.store = false;
    ex_mem.branch = false;
    ex_mem.write_data = id_ex.read_data2;
    //control_sign = [Branch MemRead MemWrite Regwrite MemtoReg]
    ex_mem.control_sign = id_ex.control_sign.substr(4,5);
    ex_mem.ALU_op = id_ex.control_sign.substr(1,2);
    if(ex_mem.control_sign[2] == '1'){//sw
        ex_mem.store = true;
    }
    if(id_ex.control_sign[0] == '1'){//R-type
        ex_mem.rt = id_ex.rd;
    }
    else{
        ex_mem.rt = id_ex.rt;
    }
    tmp1 = id_ex.read_data1;
    if(id_ex.control_sign[3] == '0'){//ALUsrc
        tmp2 = id_ex.read_data2;//r+r
    }
    else{
        tmp2 = id_ex.sign_extend;//r+16bits
    }
    ex_mem.PC = id_ex.PC+(id_ex.sign_extend*4);
    if(ex_mem.ALU_op == "00"){//lw,sw,addi
        ex_mem.ALUout = tmp1 + tmp2;
    }
    else if(ex_mem.ALU_op == "01"){//beq
        ex_mem.ALUout = tmp1 - tmp2;
        if(ex_mem.ALUout == 0){
            ex_mem.branch = true;
            if_id.PC = ex_mem.PC;
        }
    }
    else if(ex_mem.ALU_op == "10"){//R-type
        if(id_ex.func == "100000"){//add
            ex_mem.ALUout = tmp1 + tmp2;
        }
        else if(id_ex.func == "100010"){//sub
            ex_mem.ALUout = tmp1 - tmp2;
        }
        else if(id_ex.func == "100100"){//and
            ex_mem.ALUout = tmp1 & tmp2;
        }
        else if(id_ex.func == "100101"){//or
            ex_mem.ALUout = tmp1 | tmp2;
        }
        else if(id_ex.func == "101010"){//slt
            if(tmp1 < tmp2){
                ex_mem.ALUout = 1;
            }
            else{
                ex_mem.ALUout = 0;
            }
        }
    }
    else if(ex_mem.ALU_op == "11"){//andi
        ex_mem.ALUout = tmp1 & tmp2;
    }
}

//stage4:memory access
void Memory_access(){
    mem_wb.input = ex_mem.input;
    if_id.input = false;
    mem_wb.rt = ex_mem.rt;
    mem_wb.ALUout = ex_mem.ALUout;
    //control_sign = [Regwrite MemtoReg]
    mem_wb.control_sign = ex_mem.control_sign.substr(3,2);
    if(mem_wb.control_sign == "11"){//lw
        mem_wb.read_data = mem[mem_wb.ALUout/4];
    }
    else if(mem_wb.control_sign == "10"){
        mem_wb.read_data = mem_wb.ALUout;
    }
    else{
        if(ex_mem.store){//sw
            mem[mem_wb.ALUout/4] = ex_mem.write_data;
        }
        mem_wb.read_data = 0;
    }
}

//stage5:write back
void Write_back(){
    if(mem_wb.control_sign[0] == '1'){
        reg[mem_wb.rt] = mem_wb.read_data;
    }
}

//hazard check
void hazard_check(){
    //data hazard
    if(ex_mem.rt == id_ex.rs && ex_mem.rt != 0 && ex_mem.control_sign[3] == '1'){
        id_ex.read_data1 = ex_mem.ALUout;
    }
    if(ex_mem.rt == id_ex.rt && ex_mem.rt != 0 && ex_mem.control_sign[3] == '1'){
        id_ex.read_data2 = ex_mem.ALUout;
    }
    //memory hazard
    if(mem_wb.rt == id_ex.rs && ex_mem.rt != id_ex.rs && mem_wb.rt != 0 && mem_wb.control_sign[0] == '1'){
        id_ex.read_data1 = (mem_wb.control_sign[1] == '1') ? mem_wb.read_data : mem_wb.ALUout;
    }
    if(mem_wb.rt == id_ex.rt && ex_mem.rt != id_ex.rt && mem_wb.rt != 0 && mem_wb.control_sign[0] == '1'){
        id_ex.read_data2 = (mem_wb.control_sign[1] == '1') ? mem_wb.read_data : mem_wb.ALUout;
    }
    if(id_ex.control_sign[5] == '1' && (id_ex.rt == bin_dec(if_id.s.substr(6, 5)) || id_ex.rt == bin_dec(if_id.s.substr(11, 5)))){
        // set NOP
        if_id.s = "00000000000000000000000000000000";
        if_id.PC -= 4;
        if_id.input = true;
    }
    //branch hazard
    if (ex_mem.branch){
        Flush();
        Fetch();
    }
}

void Flush(){
    //if_id
    if_id.input = true;
    if_id.PC -= 4;
    if_id.s = "00000000000000000000000000000000";
    //id_ex
    id_ex.read_data1 = id_ex.read_data2 = 0;
    id_ex.sign_extend = 0;
    id_ex.rs = id_ex.rt = id_ex.rd = 0;
    id_ex.PC = 0;
    id_ex.control_sign = "000000000";
    id_ex.input = true;
}

void general(){
    initial();
    read_file("General","genResult.txt");
}

void data_hazard(){
    initial();
    read_file("Datahazard","dataResult.txt");
}

void lw_hazard(){
    initial();
    read_file("Lwhazard","loadResult.txt");
}

void branch_hazard(){
    initial();
    read_file("Branchhazard","branchResult.txt");
}

int bin_dec(string m){
    int result = 0;
    for(int i = m.length()-1,j = 0;i > 0;i--,j++){
        result += (m[i]-48)*pow(2,j);
    }
    return result;
}
