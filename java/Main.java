import java.util.Arrays;

class Buffer {
    public static final int EMPTY = 0;
    private static final int FULL = 1;
    private final int[] buffer;
    private int capacity;

    public Buffer(int size) {
        buffer = new int[size];
        this.capacity = 0;
    }

//    public int size() {return buffer.length;}

    public synchronized void produce(int index) throws InterruptedException {
        while (capacity == buffer.length) { // buffer is full
            System.out.println(Arrays.toString(buffer) + " - Buffer is full, producer waiting...");
            wait();
        }
        if (buffer[index] == EMPTY) {
            System.out.println(Arrays.toString(buffer) + " - Writing FULL (1) to element " + index);
            buffer[index] = FULL;
            capacity++;
        } else {
            System.out.println(Arrays.toString(buffer) + " - Element " + index + " is FULL, skipping operation");
        }
        notifyAll();
    }

    public synchronized void consume(int index) throws InterruptedException {
        while (capacity == 0) {
            System.out.println(Arrays.toString(buffer) + " - Buffer is empty, consumer waiting...");
            wait();
        }
        if (buffer[index] == FULL) {
            System.out.println(Arrays.toString(buffer) + " - Consuming element " + index);
            buffer[index] = EMPTY;
            capacity--;
        } else {
            System.out.println(Arrays.toString(buffer) + " - Element " + index + " is EMPTY, skipping operation");
        }
        notifyAll();
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("Building buffer of size: " + args[0]);
        int size = Integer.parseInt(args[0]);
        final Buffer buffer = new Buffer(size);
//        System.out.println(Arrays.toString(buffer));

        Thread producer = new Thread(() -> {
           int index = 0;
           while (true) {
               try {
                   buffer.produce(index++ % size);
                   Thread.sleep(500); // simulate working
               } catch (InterruptedException e) {
                   throw new RuntimeException(e);
               }
           }
        });

        Thread consumer = new Thread(() -> {
            int index = 0;
            while (true) {
                try {
                    buffer.consume(index++ % size);
                    Thread.sleep(500); // simulate working
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        producer.start();
        consumer.start();
        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}