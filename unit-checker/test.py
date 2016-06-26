from collections import namedtuple
from contextlib  import contextmanager

Test = namedtuple('Test', ['function', 'args', 'expected_output', 'check_type', 'expected_type', 'subclasses'])
Test.__new__.__defaults__ = (None, None, None, False, None, True)


class WrongType(TypeError):
    def __init__(self, message, test, output, subclass_success):
        super(WrongType, self).__init__(message)
        self.test   = test
        self.output = output
        self.subclass_success = subclass_success

class FailedTest(AssertionError):
    def __init__(self, message, test, output):
        super(WrongType, self).__init__(message)
        self.test   = test
        self.output = output

class Tester():
    def __init__(self, tests=[], num=100, verbose=True):
        self.tests   = tests
        self.num     = num
        self.verbose = verbose

    @contextmanager
    def unit_tester(self):
        try:
            yield
        except FailedTest as ft:
            print(ft.message)
            if self.verbose:
                print('Arguments: %s'       % ft.test.args)
                print('Expected output: %s' % ft.test.expected_output)
                print('Actual   output: %s' % ft.output, type(ft.output))
        else:
            print('Unit test passed')

    def test_all(self):
        for test in self.tests:
            print('Testing function %s' % test.function.__name__)
            with self.unit_tester():
                for i in range(self.num):
                    output = test.function(*test.args)
                    if not output == test.expected_output:
                        message = 'Unit test failed for function %s:' % test.function.__name__
                        raise FailedTest(message, test, output)

class Checker():
    def __init__(self, tests=[], verbose=True):
        self.tests   = tests
        self.verbose = verbose

    def check_output_type(self, test):
        output = test.function(*test.args)
        check  = False
        subclass_success = issubclass(type(output), test.expected_type)

        if test.subclasses:
            check = subclass_success
        else:
            check = type(output) is test.expected_type

        if not check:
            message = 'Output type check on function %s failed:' % test.function.__name__
            raise WrongType(message, test, output, subclass_success)

    @contextmanager
    def typeChecker(self):
        try:
            yield
        except WrongType as wt:
            print(wt.message)
            if self.verbose:
                print('Arguments: %s'              % wt.test.args)
                print('Expected output: %s of %s'  % (wt.test.expected_output, wt.test.expected_type))
                print('Actual   output: %s of %s'  % (wt.output, type(wt.output)))
                print('Subclass checking was %s'   % wt.test.subclasses)
                print('Subclass check returned %s' % wt.subclass_success)
        else:
            print('Type check passed')

    def check_types(self):
        for test in self.tests:
            if test.check_type:
                print('Checking output type on function %s' % test.function.__name__)
                with self.typeChecker():

                    self.check_output_type(test)


def id(x):
    return x

if __name__ == '__main__':
    tests   = [Test(function=id, args=[1], expected_output=1, check_type=True, expected_type=int)]
    checker = Checker(tests, verbose=True)
    checker.check_types()
    tester  = Tester(tests)
    tester.test_all()
