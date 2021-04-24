network Simulation01
{
    submodules:
        create1: Create {
            parameters:
                @display("p=50,50;i=block/source");
        }
        create2: Create {
            parameters:
                @display("p=50,150;i=block/source");
        }
        create3: Create {
            parameters:
                @display("p=50,250;i=block/source");
        }
        queue1: BlockingQueue {
            parameters:
                @display("p=150,50;i=block/boundedqueue;q=queue");
        }
        queue2: BlockingQueue {
			parameters:
                @display("p=150,150;i=block/boundedqueue;q=queue");
        }
        queue3: BlockingQueue {
			parameters:
                @display("p=150,250;i=block/boundedqueue;q=queue");
        }
        assign: Assign {
            parameters:
                @display("p=250,150;i=block/control");
        }
        queue4: Array {
			parameters:
                @display("p=750,150;i=block/boundedqueue;t");
        }
        batch: Batch {
            parameters:
                @display("p=350,250;i=block/join");
        }
        await: Lockup {
            parameters:
                @display("p=450,250;i=block/circle;q=queue");
        }
        process: Process {
            parameters:
                @display("p=550,250;i=block/process");
        }
        unbatch: Unbatch {
            parameters:
                @display("p=650,250;i=block/fork");
        }
        queue5: Array {
			parameters:
                @display("p=750,250;i=block/boundedqueue;t");
        }
        match: Match {
            parameters:
                @display("p=850,150;i=block/switch");
        }
        terminate: Terminate {
            parameters:
                @display("p=950,150;i=block/sink");
        }
        resource: Resource {
            parameters:
                @display("p=500,350;i=block/table;t");
        }
    connections:
        create1.out --> queue1.in;
        create2.out --> queue2.in;
        create3.out --> queue3.in;
        queue1.out --> assign.in1;
        queue2.out --> assign.in2;
        queue3.out --> assign.in3;
        assign.out1 --> queue4.in;
		queue4.out --> match.in1;
        assign.out2 --> batch.in;
        batch.out --> await.in;
		await.out --> process.in;
		process.out --> unbatch.in;
		unbatch.out --> queue5.in;
		queue5.out --> match.in2;
		match.out --> terminate.in;
		process.res --> resource.from_release;
		await.res --> resource.from_await;
}
