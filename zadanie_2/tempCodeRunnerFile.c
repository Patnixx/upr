y = b;
        int nums[10] = {0}; // max columns is 10
        while (y > 0)
        {
            int x = a;
            while (x > 0)
            {
            if (y == b || y == 1)
            {
                printf("x");
            }
            else if (x == a || x == 1)
            {
                printf("x");
            }
            else
            {
                // Print column number, increment for each column
                if (nums[x - 2] > 9)
                nums[x - 2] = 0;
                printf("%d", nums[x - 2]);
                nums[x - 2]++;
            }
            x--;
            }
            printf("\n");
            y--;
        }
