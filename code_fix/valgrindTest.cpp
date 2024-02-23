int main()
{
    int *x = new int(5);
    // Leak memory doesn't delete the pointer
//     LEAK SUMMARY:
// ==7706==    definitely lost: 4 bytes in 1 blocks
// ==7706==    indirectly lost: 0 bytes in 0 blocks
// ==7706==      possibly lost: 0 bytes in 0 blocks
// ==7706==    still reachable: 0 bytes in 0 blocks
// ==7706==         suppressed: 0 bytes in 0 blocks

    // After deletion:
    // All heap blocks were freed -- no leaks are possible
    delete x;
    return 0;
}