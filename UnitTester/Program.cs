using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            TestCaseBase focusedTestCase = new TestCase1();
            
            var typeList = Assembly.GetExecutingAssembly().GetTypes();
            var typeMap = new Dictionary<string, Type>();

            foreach (var iType in typeList)
            {
                if(true == iType.Name.StartsWith("TestCase"))
                {
                    typeMap.Add(iType.Name, iType);
                }
            }

            int currentCaseNumber = 1;
            while (true)
            {
                var currentTestCaseName = $"TestCase{currentCaseNumber}";
                var ret = typeMap.TryGetValue(currentTestCaseName, out var currentTestCaseType);

                if(false == ret)
                {
                    Console.WriteLine($"The '{currentTestCaseName}' not exists.");
                    break;
                }

                ++currentCaseNumber;

                var currentTestCase = Activator.CreateInstance(currentTestCaseType) as TestCaseBase;

                Debug.Assert(null != currentTestCase);

                Console.WriteLine($"{currentTestCaseName} started.");

                // Travis가 지원하는 가장 최신 VS인 2017에서는 async Main이 되는 닷넷 코어를 쓸 수 없다.
                // 그 때까지는 이렇게 Wait를 써서 async await를 사용하도록 한다.
                // FrameWork 4.7 이상, 닷넷코어 3 이상에서 async Main을 사용할 수 있다.
                currentTestCase.StartAsync().Wait();

                Console.WriteLine($"{currentTestCaseName} ended.");
            }
        }
    }
}
