///@brief Managing command line arguments passed to the program
class CommandLineArgs
{
    private:

    ///@brief list of command line args
        enum COMMAND_LINE_ARGS
        {
            Args1 = 1,
        };

    public:
        uint64_t m_arg1Value;
      
        CommandLineArgs(const int32_t &dwMaxArgsExpected, const int32_t &dwArgc, char *argv[])
        {
            if (dwArgc < dwMaxArgsExpected)
            {
                std::cout << "./myProgram Args1" << '\n';
                throw "Invalid arguments passed to program!";
            }

            m_arg1Value = atoi(argv[COMMAND_LINE_ARGS::Args1]);
   
        }
};
