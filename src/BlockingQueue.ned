simple BlockingQueue
{
    parameters:
        string qName;
        volatile double workTime @unit(s) = default(0);
    gates:
        input in;
        output out;
}
