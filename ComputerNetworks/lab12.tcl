set ns [new Simulator]

set f0 [open udp-40k.tr w]
set f1 [open udp-80k.tr w]
set f2 [open udp-120k.tr w]
set f3 [open udp-160k.tr w]

set s [$ns node]
set d [$ns node]
set r [$ns node]

$ns duplex-link $s $r 1Mb 50ms DropTail
$ns duplex-link $r $d 100kb 5ms DropTail

proc finish {} {
	global f0 f1 f2 f3
	#closing these files
	close $f0
	close $f1
	close $f2
	close $f3
	#call xgraph to display the results 
	exec xgraph udp-40k.tr udp-80k.tr udp-120k.tr udp-160k.tr -geometry 800x400 &
	exit 0
}

proc attach-expoo-traffic { node sink size burst idle rate } {
	set ns [Simulator instance]
	set source [new Agent/UDP]
	$ns attach-agent $node $source
	set traffic [new Application/Traffic/Exponential ]
	$traffic set packetSize_ $size 
	$traffic set burst_time_ $burst 
	$traffic set idle_time_ $idle 
	$traffic set rate_ $rate

	# Attach traffic source to the traffic generator
	$traffic attach-agent $source
	$ns connect $source $sink
	return $traffic 
}

proc record {} {
	global sink0 sink1 sink2 sink3 f0 f1 f2 f3
	#get an instance of the simulator 
	set ns [Simulator instance]
	#set the time after which the procedure called again
		set time 0.5
		set bw0 [$sink0 set bytes_]
		set bw1 [$sink1 set bytes_]
		set bw2 [$sink2 set bytes_]
		set bw3 [$sink3 set bytes_]
		#get the current time 
		set now [$ns now]
		#calculate the bandwidth (in Mbit/s) and write to files
		puts $f0 "$now [expr $bw0/$time*8/1000000]"
		puts $f1 "$now [expr $bw1/$time*8/1000000]"
		puts $f2 "$now [expr $bw2/$time*8/1000000]"
		puts $f3 "$now [expr $bw3/$time*8/1000000]"
		# Reset the bytes_ values of the traffic sinks 
		$sink0 set bytes_ 0
		$sink1 set bytes_ 0
		$sink2 set bytes_ 0
		$sink3 set bytes_ 0
		# Re-schedule the procedure 
		$ns at [expr $now + $time] "record"
}

set sink0 [new Agent/LossMonitor]
set sink1 [new Agent/LossMonitor]
set sink2 [new Agent/LossMonitor]
set sink3 [new Agent/LossMonitor]
$ns attach-agent $d $sink0
$ns attach-agent $d $sink1
$ns attach-agent $d $sink2
$ns attach-agent $d $sink3

set source0 [attach-expoo-traffic $s $sink0 200 2s 1s 40k]
set source1 [attach-expoo-traffic $s $sink1 200 2s 1s 80k]
set source2 [attach-expoo-traffic $s $sink2 200 2s 1s 120k]
set source3 [attach-expoo-traffic $s $sink3 200 2s 1s 160k]

$ns at 0.0 "record"
$ns at 3.0 "$source0 start"
$ns at 3.0 "$source1 start"
$ns at 3.0 "$source2 start"
$ns at 3.0 "$source3 start"
$ns at 13.0 "$source0 stop"
$ns at 13.0 "$source1 stop"
$ns at 13.0 "$source2 stop"
$ns at 13.0 "$source3 stop"
$ns at 16.0 "finish"
$ns run