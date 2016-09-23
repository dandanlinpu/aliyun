#include <iostream>
class A{
	public:
		A(){
			p = this;
			std::cout << "construct" << std::endl;
		}

		~A(){
			if (p != NULL){
				std::cout << " destruct " << std::endl;
				delete p;
				p = NULL;
			}

		}
	private:
		A *p;
};
int main()
{
A a;
return 0;
}
