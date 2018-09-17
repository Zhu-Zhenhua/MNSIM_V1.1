all:
	g++ main.cpp accuracy.cpp CalAdder.cpp CalculateGate.cpp CalDecoder.cpp CalRegister.cpp formula.cpp FunctionUnit.cpp InputParameter.cpp module.cpp Rowdecoder.cpp Technology.cpp unit_area.cpp unit_latency.cpp unit_power.cpp -o MNSIM -std=c++11
clean:
	rm MNSIM
