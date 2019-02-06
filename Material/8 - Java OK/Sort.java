//ORDENAR UM ARRAY: usar arrays.sort(...);

int[] array = new int[10];
Random rand = new Random();
for (int i = 0; i < array.length; i++)
    array[i] = rand.nextInt(100) + 1;
Arrays.sort(array);
System.out.println(Arrays.toString(array));
// in reverse order
for (int i = array.length - 1; i >= 0; i--)
    System.out.print(array[i] + " ");
System.out.println();



//ORDENAR UM ARRAYLIST: usar Collections.sort(...);

Collections.sort(mArrayList, new Comparator<CustomData>() {
    @Override
    public int compare(CustomData lhs, CustomData rhs) {
        // -1 - less than, 1 - greater than, 0 - equal, all inversed for descending
        return lhs.customInt > rhs.customInt ? -1 : (lhs.customInt < rhs.customInt) ? 1 : 0;
    }
});
