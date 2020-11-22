## ΑΡΧΙΤΕΚΤΟΝΙΚΗ ΠΡΟΗΓΜΕΝΩΝ ΥΠΟΛΟΓΙΣΤΩΝ

###1η Εργαστηριακή Άσκηση
####Εισαγωγή στον Εξομοιωτή gem5

**1.** Η εντολή που χρησιμοποιήσαμε για να τρέξουμε το precompiled πρόγραμμα _hello_ είναι η 

>$ ./build/ARM/gem5.opt configs/example/arm/starter_se.py --cpu="minor" "tests/test-progs/hello/bin/arm/linux/hello"

Σε αυτήν φαίνεται ότι δηλώνεται ρητά η χρήση του μοντέλου MinorCPU, με το argument **--cpu="minor"**, και ότι το πρόγραμμα που θα εκτελεστεί είναι το _hello_, δίνοντας το path **"tests/test-progs/hello/bin/arm/linux/hello"**.

Ανοίγοντας, τώρα, το αρχείο *starter_se.py*, μπορούμε να δούμε τα χαρακτηριστικά του συστήματος που γίνεται emulated (στην πραγματικότητα, εφόσον δουλεύουμε στην λειτουργία System Call Emulation, δεν πραγματοποιείται προσομοίωση του πλήρους συστήματος, αλλά μόνο του επεξεργαστή και του υποσυστήματος μνήμης). 

Συγκεκριμένα, στην συνάρτηση **main** φαίνονται τα arguments που περνάνε για την δημιουργία του συστήματος.

* **commands\_to\_run** (_οι εντολές που πρόκειται να εκτελεστούν_): - 
* **--cpu** (_το μοντέλο CPU που χρησιμοποιείται_): ως default χρησιμοποιείται το μοντέλο Atomic, με την εντολή όμως που χρησιμοποιήσαμε, επιλέξαμε το μοντέλο **Minor**
* **--cpu-freq** (_η συχνότητα του επεξεργαστή_): **4GHz** (default) 
* **--num-cores** (_ο αριθμός των πυρήνων του επεξεργαστή_): **1** (default)
* **--mem-type** (_ο τύπος της μνήμης που χρησιμοποιείται_): **DDR3 1600Mhz 8x8GB** (default)
* **--mem-channels** (_ο αριθμός των καναλιών μνήμης_): **2** (default)
* **--mem-ranks** (_ο αριθμός των κατηγοριών μνήμης ανά κανάλι_): -
* **--mem-size** (_το μέγεθος της φυσικής μνήμης_): **2GB** (default)  

Επίσης, στην συνάρτηση **\_\_init__** γίνεται η δημιουργία του clock και του voltage domain. Εκεί θέτουμε την συχνότητα του clock domain στο **1GHz** και την τάση του voltage domain στα **3.3 Volt**.  Στην ίδια συνάρτηση, ορίζουμε την τάση του CPU cluster στο **1.2 Volt** και το memory mode στο **timing**.
Όσον αφορά την μνήμη cache, εφόσον χρησιμοποιήσαμε το μοντέλο MinorCPU, έχουμε την **L1 Cache** και την **L2 Cache**. 

**2.** **a.** Από το αρχείο config.ini μπορούμε να εξάγουμε τις εξής πληροφορίες για το σύστημα:  

* Line 20: **mem_mode = timing** (_η λειτουργία της μνήμης_)
* Line 44: **clock = 1000**, το οποίο αντιστοιχεί σε **1GHz** (_η συχνότητα του clock domain_)
* Line 58: **clock = 250**, το οποίο αντιστοιχεί σε **4GHz** (_η συχνότητα του επεξεργαστή_)
* Line 65:  **type = MinorCPU** (_το μοντέλο CPU που χρησιμοποιείται_)
* Line 113: **numThreads = 1** (_ο αριθμός των πυρήνων του επεξεργαστή_)
* Line 1339: **voltage=1.2** (_η τάση του CPU cluster_)
* Line 1349 και Line 1479:  **system.mem\_ctrls0** και **system.mem\_ctrls1**, άρα **2** (_ο αριθμός των καναλιών μνήμης_) 
* Line 1376: **type = DRAMInterface** (?) (_ο τύπος της μνήμης που χρησιμοποιείται_)
* Line 1652: **voltage = 3.3** (_η τάση του voltage domain_)

**b.** Από το stats.txt, βλέπουμε στο Line 14 ότι το συνολικό νούμερο των commited εντολών είναι **5028**.  

**c.** Από το stats.txt, βλέπουμε στο Line 493 ότι η L2 προσπελάστηκε **479** φορές. Χωρίς την βοήθεια του εξομοιωτή, θα μπορούσαμε να υπολογίσουμε τον αριθμό των φορών που προσπελάστηκε η L2 ως εξής: _μπλα μπλα μπλα_

**3.** Τα in-order μοντέλα CPU που χρησιμοποιούνται από τον gem5 είναι:

* **Simple CPU**:
	* **BaseSimpleCPU**:
	* **AtomicSimpleCPU**:
	* **Timing SimpleCPU**:
* **Minor CPU**:  

**a.**Το πρόγραμμα που γράφτηκε σε C είναι ένας απλός υπολογισμός των αριθμών Fibonacci, για τους πρώτους 10 αριθμούς. Κατά την εκτέλεσή του χρησιμοποιήθηκαν τα μοντέλα TimingSimpleCPU και MinorCPU. Από τα stats.txt, εξάγαμε τις εξής πληροφορίες για τους χρόνους εκτέλεσης:

* **TimingSimpleCPU**: Line 12 του stats.txt: **sim\_seconds = 0.000048** (_δευτερόλεπτα που περνούν μέσα στην προσομοίωση για την εκτέλεση του προγράμματος_) 
* **MinorCPU**: Line 12 του stats.txt: **sim\_seconds = 0.000039**

**b.** Οι διαφορές στους παραπάνω χρόνους εκτέλεσης έγκεινται στο ότι (?). Τα όμοια αποτελέσματα δικαιολογούνται από το ότι (?).

**c.** Αλλάζοντας την συχνότητα λειτουργίας, παρατηρούμε ότι (?).

###ΠΗΓΕΣ

Οι πηγές που χρησιμοποιήσαμε για την εκπόνηση αυτής τις εργασίες είναι:

1. [http://learning.gem5.org/book/part1/simple_config.html](http://learning.gem5.org/book/part1/simple_config.html)
2. [http://learning.gem5.org/book/part1/gem5_stats.html](http://learning.gem5.org/book/part1/gem5_stats.html)
3. [http://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU](http://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU)
4. [http://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu](http://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu)

***

###ΚΡΙΤΙΚΗ

 






