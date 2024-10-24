#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<int> stringToVector(const std::string& number) {
    std::vector<int> result;
    for (char digit : number) {
        result.push_back(digit - '0');
    }
    return result;
}
std::vector<int> IntTovector(int s){
std::vector<int> result;


int number = std::abs(s);


if (number == 0) {
    result.push_back(0);
} else {
    
    while (number > 0) {
        result.insert(result.begin(), number % 10);
        number /= 10;
    }
}

return result;
}

bool operator==(const std::vector<int>& key1, const std::vector<int>& key2) {
    if (key1.size() != key2.size()) {
        return false;
    }

    for (size_t i = 0; i < key1.size(); ++i) {
        if (key1[i] != key2[i]) {
            return false;
        }
    }
    
    return true;
}

bool isGreaterOrEqual(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    if (vec1.size() > vec2.size()) return true;
    if (vec1.size() < vec2.size()) return false;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] > vec2[i]) return true;
        if (vec1[i] < vec2[i]) return false;
    }
    return true;
}


std::vector<int> operator+(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    size_t size = std::max(vec1.size(), vec2.size());
    std::vector<int> result(size + 1, 0);

  
    std::vector<int> v1 = vec1, v2 = vec2;
    if (v1.size() < size) v1.insert(v1.begin(), size - v1.size(), 0);
    if (v2.size() < size) v2.insert(v2.begin(), size - v2.size(), 0);

    int carry = 0;
    for (int i = size - 1; i >= 0; --i) {
        int sum = v1[i] + v2[i] + carry;
        result[i + 1] = sum % 10;
        carry = sum / 10;
    }
    result[0] = carry;

   
    if (result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}


std::vector<int> operator-(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    size_t size = std::max(vec1.size(), vec2.size());
    std::vector<int> result(size, 0);

 
    std::vector<int> v1 = vec1, v2 = vec2;
    if (v1.size() < size) v1.insert(v1.begin(), size - v1.size(), 0);
    if (v2.size() < size) v2.insert(v2.begin(), size - v2.size(), 0);

    int borrow = 0;
    for (int i = size - 1; i >= 0; --i) {
        int sub = v1[i] - v2[i] - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = sub;
    }


    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}


std::vector<int> operator*(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    std::vector<int> result(vec1.size() + vec2.size(), 0);

    for (int i = vec1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = vec2.size() - 1; j >= 0; --j) {
            int mul = vec1[i] * vec2[j] + result[i + j + 1] + carry;
            result[i + j + 1] = mul % 10;
            carry = mul / 10;
        }
        result[i] += carry;
    }

    
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}


std::vector<int> operator/(const std::vector<int>& dividend, const std::vector<int>& divisor) {
    std::vector<int> result;
    std::vector<int> current;

    for (size_t i = 0; i < dividend.size(); ++i) {
        current.push_back(dividend[i]);


        while (current.size() > 1 && current[0] == 0) {
            current.erase(current.begin());
        }

        int count = 0;
        while (isGreaterOrEqual(current, divisor)) {
            current = current - divisor;
            count++;
        }
        result.push_back(count);
    }

   
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}
std::vector<int> operator^(std::vector<int> key1,int e){
    std::string s="1";
    std::vector<int> result;
    result=stringToVector(s);
    for(int i=0;i<e;i++){
        result=result*key1;
    }
    
    
    
    return result;
}



std::vector<int> operator%(const std::vector<int>& dividend, const std::vector<int>& divisor) {
    if (divisor.size() == 1 && divisor[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    std::vector<int> current;

    for (size_t i = 0; i < dividend.size(); ++i) {
        current.push_back(dividend[i]);

        while (current.size() > 1 && current[0] == 0) {
            current.erase(current.begin());
        }

        while (isGreaterOrEqual(current, divisor)) {
            current = current - divisor;
        }
    }

    return current;
}

std::vector<int> operator^(const std::vector<int>& base, const std::vector<int>& exponent) {
    if (base.size() == 1 && base[0] == 0) {
        return {0};
    }

    if (exponent.size() == 1 && exponent[0] == 0) {
        return {1};
    }

    std::vector<int> result = {1};
    std::vector<int> baseCopy = base;
    std::vector<int> exp = exponent;



    while (!(exp.size() == 1 && exp[0] == 0)) {
     


        if (isGreaterOrEqual(exp, stringToVector("1")) && exp.back() % 2 == 1) {
            result = result * baseCopy;
   
        }

     
        baseCopy = baseCopy * baseCopy;
   

      
        exp = exp / IntTovector(2);
    }

    return result;
}





/*std::vector<int> operator^(const std::vector<int>& base, const std::vector<int>& exponent) {
    if (base.size() == 1 && base[0] == 0) {
        return {0};
    }
    
    if (exponent.size() == 1 && exponent[0] == 0) {
        return {1};
    }
    
    std::string s1 = "1";
    std::string s0 = "0";
    std::vector<int> single = stringToVector(s1);
    std::vector<int> indicator = stringToVector(s0);
    std::vector<int> result = base;
    
    
    
    
    
    
    while (!(indicator == (exponent - single))) {
            result = result * base;
            indicator = indicator + single;
            for(int i:indicator){
                std::cout<<i;
            }
            std::cout<<"\n";
        }
    }
        return result;
    
}*/



std::vector<int> eyler_function(std::vector<int> key1,std::vector<int> key2) {
    std::string s="1";
    std::vector<int> s1=stringToVector(s);
    key1=key1-s1;
    key2=key2-s1;
    std::vector<int> result=key1*key2;

    return result;
}

std::vector<int> secret_exponent(std::vector<int> &key1,std::vector<int> &key2,int e){
    std::string s="1";
    std::vector<int> s1=stringToVector(s);
    std::vector<int> e_in_vector=IntTovector(e);
    
 
    int random_number = 2;
    std::vector<int>random_number_in_vector=IntTovector(random_number);
    std::vector<int> result=((random_number_in_vector*eyler_function(key1,key2))+s1)/e_in_vector;
    return result;
}









void printVector(const std::vector<int>& vec) {
    for (int value : vec) {
        std::cout << value;
    }
    std::cout << std::endl;
}
                                 

int main() {
    std::string num1 = "503";//389
    std::string num2 = "509";//467
  
    int e1=3;
    std::string message;
    std::cout<<"Введите кодовое слово \n";
    std::cin>>message;
    std::vector<int> message_scrypt = stringToVector(message);
    std::vector<int> vector1 = stringToVector(num1);
    std::vector<int> vector2 = stringToVector(num2);
    std::cout<<"Подождите,идет шифрование \n";
    std::vector<int> scrypt=(message_scrypt^e1)%(vector1*vector2);
    std::cout<<"\n";
    std::cout<<"Зашифрованный текст \n";
    printVector(scrypt);
    std::cout<<"Подождите, идет расшифровывание \n";
    std::vector<int> secret=secret_exponent(vector1, vector2,e1);
    std::vector<int> descypt=(scrypt^secret_exponent(vector1, vector2,e1))%(vector1*vector2);
    std::cout<<"Расшифрованный текст \n";
    printVector(descypt);
    return 0;
}

