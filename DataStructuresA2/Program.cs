// Bar Mashiach 315111849 בר משיח   
// Ran Kadori 209534486 רן כדורי

using System;

namespace DataStructuresA2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();

            // Generate arrays
            int[] arr = new int[100];
            for (int i = 0; i < arr.Length; i++)
                arr[i] = rnd.Next(100, 1000);

            // Print arrays
            Console.WriteLine("Array:");
            Console.WriteLine(string.Join(", ", arr));
            Console.WriteLine();

            // Run methods
            var iterative = MaxProfitIterative(arr);
            var dc = MaxProfitDC(arr);

            // Results
            Console.WriteLine("Iterative O(n):");
            Console.WriteLine($"Smaller = {iterative.Min}, Larger = {iterative.Max}, Difference = {iterative.Diff}");

            Console.WriteLine();

            Console.WriteLine("Divide & Conquer O(n):");
            Console.WriteLine($"Smaller = {dc.Min}, Larger = {dc.Max}, Difference = {dc.Diff}");
        }

        // Stock running problem 0(n)
        public static (int Min, int Max, int Diff) MaxProfitIterative(int[] prices)
        {
            if (prices == null || prices.Length < 2)
                return (0, 0, 0);

            int minSoFar = prices[0];
            int best = 0, bestMin = prices[0], bestMax = prices[0];

            for (int i = 1; i < prices.Length; i++)
            {
                int profit = prices[i] - minSoFar;
                if (profit > best)
                {
                    best = profit;
                    bestMin = minSoFar;
                    bestMax = prices[i];
                }
                if (prices[i] < minSoFar) minSoFar = prices[i];
            }

            return (bestMin, bestMax, best);
        }

        // Divide and conquer improved O(n)
        public static (int Min, int Max, int Diff) MaxProfitDC(int[] prices)
        {
            if (prices == null || prices.Length < 2)
                return (0, 0, 0);

            var res = Solve(prices, 0, prices.Length - 1);
            return (res.Buy, res.Sell, res.Best);
        }

        private readonly record struct Frag(int Min, int Max, int Best, int Buy, int Sell);

        private static Frag Solve(int[] a, int l, int r)
        {
            if (l == r) return new Frag(a[l], a[l], 0, a[l], a[l]);

            int m = (l + r) / 2;
            var left = Solve(a, l, m);
            var right = Solve(a, m + 1, r);

            int cross = right.Max - left.Min;
            int best = left.Best;
            int buy = left.Buy, sell = left.Sell;

            if (right.Best > best)
            {
                best = right.Best;
                buy = right.Buy;
                sell = right.Sell;
            }

            if (cross > best)
            {
                best = cross;
                buy = left.Min;
                sell = right.Max;
            }

            int min = Math.Min(left.Min, right.Min);
            int max = Math.Max(left.Max, right.Max);

            return new Frag(min, max, best, buy, sell);
        }
    }
}