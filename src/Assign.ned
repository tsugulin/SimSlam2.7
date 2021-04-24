simple Assign
{
    parameters:
        volatile double workTime1 @unit(s) = default(0);
        volatile double workTime2 @unit(s) = default(0);
		volatile double workTime3 @unit(s) = default(0);
	gates:
        input in1;
        input in2;
        input in3;
        output out1;
        output out2;
}
