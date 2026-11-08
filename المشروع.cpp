// 1. هيكلة بيانات الطالب (Class & Constructor)
class Student {
    constructor(id, name, grades, attendance) {
        this.id = id;
        this.name = name;
        this.grades = grades;          // مصفوفة درجات 3 مواد
        this.attendance = attendance;  // نسبة الحضور
    }

    // دالة حساب المتوسط باستخدام reduce
    calculateAverage() {
        const sum = this.grades.reduce((acc, grade) => acc + grade, 0);
        return sum / this.grades.length;
    }

    // دالة التقدير
    getGrade(average) {
        if (average >= 90) return 'A';
        if (average >= 80) return 'B';
        if (average >= 70) return 'C';
        if (average >= 60) return 'D';
        if (average >= 50) return 'E';
        return 'F';
    }

    // دالة النتيجة النهائية
    getStatus() {
        const average = this.calculateAverage();
        if (average >= 50 && this.attendance >= 75) {
            return "ناجح";
        } else {
            return "يحتاج مراجعة";
        }
    }
}

// 3. نظام تشغيل الجامعة (Objects Array)
const studentsList = [
    new Student(101, "أحمد محمد", [85, 90, 88], 85),
    new Student(102, "محمود هشام", [44, 46, 45], 80),  // طالب متعثر
    new Student(103, "فاطمة علي", [72, 75, 78], 90),
    new Student(104, "سارة أحمد", [42, 40, 43], 70)    // طالب متعثر
];

console.log("=========================================");
console.log("       تقرير نظام نتائج الطلاب العام        ");
console.log("=========================================");

studentsList.forEach(student => {
    const avg = student.calculateAverage();
    console.log(`الاسم: ${student.name} | رقم الجلوس: ${student.id} | المتوسط: ${avg.toFixed(2)} | التقدير: ${student.getGrade(avg)} | النتيجة: ${student.getStatus()}`);
});

// 4. لجنة الرأفة (Array Methods)
const strugglingStudents = studentsList.filter(student => {
    const avg = student.calculateAverage();
    return avg >= 40 && avg < 50;
});

const mercyProcessedStudents = strugglingStudents.map(student => {
    const originalAvg = student.calculateAverage();
    const newAvg = originalAvg + 5;
    return {
        id: student.id,
        name: student.name,
        originalAverage: originalAvg,
        newAverage: newAvg,
        newStatus: newAvg >= 50 ? "ناجح بالرأفة" : "يحتاج مراجعة"
    };
});

const totalNewAverages = mercyProcessedStudents.reduce((sum, student) => sum + student.newAverage, 0);
const count = mercyProcessedStudents.length;
const generalMercyAverage = count > 0 ? totalNewAverages / count : 0;

// 5. المخرجات (Console Logging)
console.log("\n=========================================");
console.log("      تقرير لجنة الرأفة للطلاب المتعثرين     ");
console.log("=========================================");

console.table(mercyProcessedStudents);

console.log(`\n[درع الحماية مفعل]: عدد الطلاب المتعثرين = ${count}`);
console.log(`المتوسط العام لدرجات المتعثرين بعد إضافة درجات الرأفة: ${generalMercyAverage.toFixed(2)}`);
console.log("=========================================");