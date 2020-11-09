import unittest
import dna


class CalcTest(unittest.TestCase):

    def test_1(self):
        self.assertEqual(dna.main('databases/small.csv', 'sequences/1.txt'), 'Bob')

    def test_2(self):
        self.assertEqual(dna.main('databases/small.csv', 'sequences/2.txt'), 'No match')

    def test_3(self):
        self.assertEqual(dna.main('databases/small.csv', 'sequences/3.txt'), 'No match')

    def test_4(self):
        self.assertEqual(dna.main('databases/small.csv', 'sequences/4.txt'), 'Alice')

    def test_5(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/5.txt'), 'Lavender')

    def test_6(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/6.txt'), 'Luna')

    def test_7(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/7.txt'), 'Ron')

    def test_8(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/8.txt'), 'Ginny')

    def test_9(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/9.txt'), 'Draco')

    def test_10(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/10.txt'), 'Albus')

    def test_11(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/11.txt'), 'Hermione')

    def test_12(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/12.txt'), 'Lily')

    def test_13(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/13.txt'), 'No match')

    def test_14(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/14.txt'), 'Severus')

    def test_15(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/15.txt'), 'Sirius')

    def test_16(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/16.txt'), 'No match')

    def test_17(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/17.txt'), 'Harry')

    def test_18(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/18.txt'), 'No match')

    def test_19(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/19.txt'), 'Fred')

    def test_20(self):
        self.assertEqual(dna.main('databases/large.csv', 'sequences/20.txt'), 'No match')


if __name__ == '__main__':
    unittest.main()
