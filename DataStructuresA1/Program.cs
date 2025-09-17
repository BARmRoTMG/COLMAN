// בר משיח 315111849
// רן כדורי 209534486

namespace DataStructuresA1
{
    internal class Program
    {
        private static readonly Random Rand = new Random();

        static void Main(string[] args)
        {
            int[] V = GenerateArray();
            int m = V.Length;
            int x = Rand.Next(1, 100);

            int s1 = Search1(V, m, x);
            int s2 = Search2(V, m, x);
            int s3 = Search3(V, m, x);

            Console.WriteLine($"x={x}, s1={s1}, s2={s2}, s3={s3}");

            // Trials
            const int trials = 500;
            long total1 = 0, total2 = 0, total3 = 0;

            for (int t = 0; t < trials; t++)
            {
                int[] VV = GenerateArray();
                int mm = VV.Length;
                int xx = Rand.Next(1, 100);

                int comps = 0;
                Search1Count(VV, mm, xx, ref comps);
                total1 += comps;

                comps = 0;
                Search2Count(VV, mm, xx, ref comps);
                total2 += comps;

                comps = 0;
                Search3Count(VV, mm, xx, ref comps);
                total3 += comps;
            }

            Console.WriteLine("200<=n<=300");
            Console.WriteLine($"Search1: {total1 / (double)trials:F2}");
            Console.WriteLine($"Search2: {total2 / (double)trials:F2}");
            Console.WriteLine($"Search3: {total3 / (double)trials:F2}");
        }
        private static int[] GenerateArray()
        {
            var arr = new int[1000];
            int n = Rand.Next(200, 301);

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

        // Binary Search O(logm)
        private static int Search2(int[] V, int m, int x)
        {
            int lo = 0, hi = m;
            while (lo < hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                if (V[mid] == 0) hi = mid;
                else lo = mid + 1;
            }
            int n = lo;

            int left = 0, right = n - 1;
            while (left <= right)
            {
                int mid = left + ((right - left) >> 1);
                if (V[mid] == x) return mid;
                if (V[mid] < x) left = mid + 1;
                else right = mid - 1;
            }
            return -1;
        }

        // Exponential Search O(logn)
        private static int Search3(int[] V, int m, int x)
        {
            if (m == 0 || V[0] == 0) return -1;

            int low = 0;
            int high = 1;
            while (high < m && V[high] != 0)
            {
                low = high;
                high <<= 1;
            }
            if (high > m) high = m;

            int left = low + 1, right = high;
            while (left < right)
            {
                int mid = left + ((right - left) >> 1);
                if (V[mid] == 0) right = mid;
                else left = mid + 1;
            }
            int n = left;

            int lo = 0, hi = n - 1;
            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                if (V[mid] == x) return mid;
                if (V[mid] < x) lo = mid + 1;
                else hi = mid - 1;
            }
            return -1;
        }

        // Counters
        private static int Search1Count(int[] V, int m, int x, ref int comps)
        {
            for (int i = 0; i < m; i++)
            {
                comps++; if (V[i] == 0) break;
                comps++; if (V[i] == x) return i;
            }
            return -1;
        }

        private static int Search2Count(int[] V, int m, int x, ref int comps)
        {
            int lo = 0, hi = m;
            while (lo < hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                comps++;
                if (V[mid] == 0) hi = mid; else lo = mid + 1;
            }
            int n = lo;

            int left = 0, right = n - 1;
            while (left <= right)
            {
                int mid = left + ((right - left) >> 1);
                comps++; if (V[mid] == x) return mid;
                comps++;
                if (V[mid] < x) left = mid + 1; else right = mid - 1;
            }
            return -1;
        }

        private static int Search3Count(int[] V, int m, int x, ref int comps)
        {
            if (m == 0) return -1;
            comps++; if (V[0] == 0) return -1;

            int low = 0, high = 1;
            while (high < m)
            {
                comps++; if (V[high] == 0) break;
                low = high;
                high <<= 1;
                if (high > m) { high = m; break; }
            }

            int left = low + 1, right = high;
            while (left < right)
            {
                int mid = left + ((right - left) >> 1);
                comps++; if (V[mid] == 0) right = mid; else left = mid + 1;
            }
            int n = left;

            int lo = 0, hi = n - 1;
            while (lo <= hi)
            {
                int mid = lo + ((hi - lo) >> 1);
                comps++; if (V[mid] == x) return mid;
                comps++;
                if (V[mid] < x) lo = mid + 1; else hi = mid - 1;
            }
            return -1;
        }
    }
}