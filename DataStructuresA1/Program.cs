namespace DataStructuresA1
{
    internal class Program
    {
        private static readonly Random Rand = new Random();

        static void Main(string[] args)
        {
            int[] V = GenerateArray();
            int m = V.Length;                 // use the full array length (1000)
            int x = Rand.Next(1, 100);        // same range as GenerateArray

            int s1 = Search1(V, m, x);
            Search2();
            Search3();

            Console.WriteLine($"x={x}, idx={s1}");
        }
        private static int[] GenerateArray()
        {
            var arr = new int[1000];
            int n = Rand.Next(0, arr.Length + 1);

            for (int i = 0; i < n; i++)
                arr[i] = Rand.Next(1, 100);

            Array.Sort(arr, 0, n);
            return arr;
        }

        // Linear Search O(n)
        private static int Search1(int[] V, int m, int x)
        {
            for (int i = 0; i < m; i++)
            {
                if (V[i] == 0) break;
                if (V[i] == x) return i;
            }
            return -1;
        }

        private static int Search2()
        {
            return 1;
        }

        private static int Search3()
        {
            return 1;
        }
    }
}