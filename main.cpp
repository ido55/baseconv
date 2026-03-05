// baseconv - A CLI number base converter
// Description: Converts numbers between binary, decimal and hexadecimal
// Usage: baseconv <value> --from <base> --to <base>

#include <clocale>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <vector>


using namespace std;

long long toDecimal(const string& value, const string& from){
    try{
    if(from == "dec") return stoll(value);
    if(from == "hex") return stoll(value,nullptr, 16);
    if(from =="bin") return stoll(value,nullptr,2);
    throw invalid_argument("Unknown source base: "+ from);
    }catch(const invalid_argument&){
        throw invalid_argument(
            "Invalid value '" + value + "' for base " + from + ".\n"
            "  bin only allows: 0 1\n"
            "  hex only allows: 0-9 A-F\n"
            "  dec only allows: 0-9");
    } catch (const std::out_of_range&) {
        throw std::out_of_range(
            "Value '" + value + "' is too large to convert."
        );
    }

}

string fromDecimal(long long value, const string& to){
    if(to == "dec") return to_string(value);
    if (to == "hex"){
        if(value ==0) return "0";
        string result;
        const char* digits = "0123456789ABCDEF";
        while (value >0){
            result += digits[value%16];
            value /=16;
        }
        reverse(result.begin(),result.end());
        return result;
    }
    if ( to =="bin"){
        if(value ==0) return "0";
        string result;
        while(value >0){
            result += (value %2 ==0) ? '0':'1';
            value/=2;
        }
        reverse(result.begin(),result.end());
        return result;
    }
    throw std::invalid_argument("Unknown target base: " + to);
}

struct Args{
    string value;
    string from;
    string to;
};

void printUsage(){
    cout << "Usage: baseconv <value> --from <base> --to <base>\n"
              << "Bases: dec, hex, bin\n"
              << "Examples:\n"
              << "  baseconv 255 --from dec --to hex\n"
              << "  baseconv FF  --from hex --to bin\n"
              << "  baseconv 11111111 --from bin --to dec\n"; 
}

Args parseArgs(int argc, char* argv[]){
    if (argc != 6){
        printUsage(); exit(1);
    }

    Args args;
    args.value = argv[1];

    map<string,string*> flags = {
        {"--from", &args.from}, {"--to", &args.to}
    };

    for (int i =2; i< argc; i+=2){
        auto it = flags.find(argv[i]);
        if (it == flags.end()){
            cerr << "Unknown flags: " << argv[i] << "\n";
            printUsage(); exit(1);
        }
        *it -> second = argv[i+1];
    }

    //validating the bases:
    const vector<string> validBases = {"dec","hex","bin"};
    auto isValid = [&](const string& base){
        return find(validBases.begin(),validBases.end(),base) != validBases.end();
    };
    if (!isValid(args.from)){
        cerr << "ERROR:unknown source base ' " << args.from << " '. valid options are dec,hex,bin\n";
        exit(1);}
    if (!isValid(args.to))
        {cerr << "ERROR:unknown source base ' " << args.to << " '. valid options are dec,hex,bin\n";
        exit(1);}

    return args;
}


int main(int argc, char* argv[]){
    try{
        Args args = parseArgs(argc, argv);
        long long decimal = toDecimal(args.value, args.from);
        string result = fromDecimal(decimal,args.to);
        cout << result << "\n";
    } catch(const exception& e){
        cerr << "ERROR: " << e.what() << "\n";
        return 1;
    } 
    return 0;
    
}


