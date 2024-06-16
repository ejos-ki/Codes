/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */
package oop_project;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.table.*;
import java.io.IOException;
/**
 *
 * @author Acer
 */
public class StudentGradingSystem extends javax.swing.JFrame {

    private String userID;
    private String lastName;
    private String firstname;
    private String course;
    
    private String[] STUDENTS;
    
    public static Object[][] sem1GradeData;
    public static Object[][] sem2GradeData;
    
    private Object[] deletedRowData;
    
    private String[] readStudentIDs() {
        ArrayList<String> studentIDsList = new ArrayList<>();

        try {
            File accountsFile = new File("STUDENT_ACCOUNT.txt");
            BufferedReader reader = new BufferedReader(new FileReader(accountsFile));
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\s+");

                // Assuming the USERID is the fourth element in each line
                if (parts.length >= 4) {
                    studentIDsList.add(parts[2]); // Assuming USERID is at index 2
                }
            }

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return studentIDsList.toArray(new String[0]);
    }
    
    private void populateStudentIDs() {
        for (String id : STUDENTS) {
            STUDENTID.addItem(id);
        }
    }

    // Getter method for accessing SEM1GRADE data
    public Object[][] getSem1GradeData() {
        if (sem1GradeData == null) {
            int rows = SEM1GRADE.getRowCount();
            int cols = SEM1GRADE.getColumnCount();
            
            sem1GradeData = new Object[rows][cols];

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    sem1GradeData[i][j] = SEM1GRADE.getValueAt(i, j);
                }
            }
        }
        return sem1GradeData;
    }

    // Getter method for accessing SEM2GRADE data
    public Object[][] getSem2GradeData() {
        if (sem2GradeData == null) {
            int rows = SEM2GRADE.getRowCount();
            int cols = SEM2GRADE.getColumnCount();
            
            sem2GradeData = new Object[rows][cols];

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    sem2GradeData[i][j] = SEM2GRADE.getValueAt(i, j);
                }
            }
        }
        return sem2GradeData;
    }

    /**
     * Creates new form StudentGradingSystem
     */
    public StudentGradingSystem(String userID, String lastName, String firstname, String course) {
        initComponents();
        
        this.userID = userID;
        this.lastName = lastName;
        this.firstname = firstname;
        this.course = course;
        
        // Update the NAME label with the desired format
        NAME.setText(course + " || " + userID + " | " + lastName + ", " + firstname);
        
        STUDENTS = readStudentIDs();
        
        populateStudentIDs(); // Populate the STUDENTID combobox
        
        S1.setSelected(true);
        
        // Add action listeners to the checkboxes
        S1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                if (S1.isSelected()) {
                    SEM1PANEL.setVisible(true);
                    SEM2PANEL.setVisible(false);
                } else {
                    SEM1PANEL.setVisible(false);
                }
            }
        });

        S2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                if (S2.isSelected()) {
                    SEM2PANEL.setVisible(true);
                    SEM1PANEL.setVisible(false);
                } else {
                    SEM2PANEL.setVisible(false);
                }
            }
        });
        
        loadSavedData();
        checkUserData();
    }

    private void setUpSetButton() {
        SET.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
            
            boolean isValid = validateInputs();
            if (isValid) {
                updateDataToFile();
                disableComponents(true);
                enableComponents(false);
                MODIFY.setEnabled(true);
            }}
        });
    }

    private boolean validateInputs() {
        if (QUIZPER.getSelectedIndex() == 0 || EXAMPER.getSelectedIndex() == 0 || PTPER.getSelectedIndex() == 0 ||
                QUIZITEM.getText().isEmpty() || EXAMITEM.getText().isEmpty() || PTITEM.getText().isEmpty()) {
            JOptionPane.showMessageDialog(null, "Please complete all the fields");
            return false; // Exit if any field is empty or combo box not selected
        }

        double totalPercentage = Double.parseDouble(QUIZPER.getSelectedItem().toString()) +
                Double.parseDouble(EXAMPER.getSelectedItem().toString()) +
                Double.parseDouble(PTPER.getSelectedItem().toString());

        if (totalPercentage != 100) {
            JOptionPane.showMessageDialog(null, "Total Percentage must reach 100");
            return false; // Exit if total percentage is not 1.00
        }

        try {
            double quizValue = Double.parseDouble(QUIZITEM.getText());
            double examValue = Double.parseDouble(EXAMITEM.getText());
            double ptValue = Double.parseDouble(PTITEM.getText());

            if (quizValue < 0 || examValue < 0 || ptValue < 0) {
                JOptionPane.showMessageDialog(null, "Items must be a positive number");
                return false; // Exit if any input is negative
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Invalid input! Items must be a number.");
            return false; // Exit if input is not a number
        }

        return true; // All validation checks passed
    }

    private void updateDataToFile() {
        String dataToWrite = userID + " " +
                QUIZPER.getSelectedItem().toString() + " " +
                EXAMPER.getSelectedItem().toString() + " " +
                PTPER.getSelectedItem().toString() + " " +
                QUIZITEM.getText() + " " +
                EXAMITEM.getText() + " " +
                PTITEM.getText();

        try {
            File file = new File("PERCE_ITEMS.txt");
            File tempFile = new File("TEMP_PERCE_ITEMS.txt");

            if (!file.exists()) {
                file.createNewFile();
            }

            BufferedReader reader = new BufferedReader(new FileReader(file));
            BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile));

            String line;
            boolean foundUserID = false;

            while ((line = reader.readLine()) != null) {
                if (line.startsWith(userID)) {
                    writer.write(dataToWrite + "\n");
                    foundUserID = true;
                } else {
                    writer.write(line + "\n");
                }
            }

            reader.close();
                        
            if (!foundUserID) {
                writer.write(dataToWrite + "\n");
            }

            writer.close();

            // Delete the original file
            if (!file.delete()) {
                System.out.println("Failed to delete the file.");
                return;
            }

            // Rename the temporary file to the original file name
            if (!tempFile.renameTo(file)) {
                System.out.println("Failed to rename the file.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void checkUserData() {
        try {
            File file = new File("PERCE_ITEMS.txt");
            if (!file.exists()) {
                System.out.println("File does not exist.");
                setUpSetButton(); // If the file doesn't exist, set up as new
                disableComponents(false);
                return;
            }

            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            boolean foundUserID = false;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\s+");

                if (parts[0].equals(userID)) {
                    // If USERID is found in the file
                    QUIZPER.setSelectedItem(parts[1]);
                    EXAMPER.setSelectedItem(parts[2]);
                    PTPER.setSelectedItem(parts[3]);

                    QUIZITEM.setText(parts[4]);
                    EXAMITEM.setText(parts[5]);
                    PTITEM.setText(parts[6]);

                    foundUserID = true;
                    break; // Exit the loop once data is found for the USERID
                }
            }

            reader.close();

            if (foundUserID) {
                disableComponents(true);
                enableComponents(false);
                setUpSetButton();
            }else {
                // If USERID is not found in the file
                disableComponents(false);
                enableComponents(true);                
                setUpSetButton(); // Set up as new if USERID is not found
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void disableComponents(boolean isEnabled) {
        // Disable components
        QUIZ.setEnabled(isEnabled);
        FINAL.setEnabled(isEnabled);
        MIDTERM.setEnabled(isEnabled);
        PT.setEnabled(isEnabled);
        STUDENTID.setEnabled(isEnabled);
        UPDATE.setEnabled(isEnabled);
        DROP.setEnabled(isEnabled);
        S1.setEnabled(isEnabled);
        S2.setEnabled(isEnabled);
        LAYER.setEnabled(isEnabled);
        SEM1PANEL.setEnabled(isEnabled);
        SEM1GRADE.setEnabled(isEnabled);
        SEM2PANEL.setEnabled(isEnabled);
        SEM2GRADE.setEnabled(isEnabled);
        A.setEnabled(isEnabled);
        B.setEnabled(isEnabled);
        MODIFY.setEnabled(isEnabled);
    }

    public void enableComponents(boolean isEnabled) {
        // Enable components
        QUIZPER.setEnabled(isEnabled);
        EXAMPER.setEnabled(isEnabled);
        PTPER.setEnabled(isEnabled);
        QUIZITEM.setEnabled(isEnabled);
        EXAMITEM.setEnabled(isEnabled);
        PTITEM.setEnabled(isEnabled);
        SET.setEnabled(isEnabled);
    }

    private boolean isStudentIDAlreadyExists(DefaultTableModel model, String studentID) {
        for (int i = 0; i < model.getRowCount(); i++) {
            String existingID = model.getValueAt(i, 1).toString(); // Assuming column 2 contains student IDs

            if (existingID.equals(studentID)) {
                return true; // Student ID already exists in the table
            }
        }
        return false; // Student ID doesn't exist in the table
    }
    
    private void updateSEM1DATA() {
        int rows = SEM1GRADE.getRowCount();
        int cols = SEM1GRADE.getColumnCount();
        sem1GradeData = new Object[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sem1GradeData[i][j] = SEM1GRADE.getValueAt(i, j);
            }
        }
    }

    private void updateSEM2DATA() {
        int rows = SEM2GRADE.getRowCount();
        int cols = SEM2GRADE.getColumnCount();
        sem2GradeData = new Object[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sem2GradeData[i][j] = SEM2GRADE.getValueAt(i, j);
            }
        }
    }
    
    public void saveDataToFile(Object[][] data, String filename) {
        Set<String> existingLines = new HashSet<>();
        List<String> newLines = new ArrayList<>();

        // Read the existing file content and store it in a Set
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                existingLines.add(line.trim());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Process and append new data only if it doesn't already exist in the file
        for (Object[] row : data) {
            StringBuilder rowString = new StringBuilder();
            rowString.append(userID).append(" ");
            rowString.append(course).append(" ");
            for (Object cell : row) {
                rowString.append(cell).append("\t");
            }
            String newRow = rowString.toString().trim();
            if (!existingLines.contains(newRow)) {
                newLines.add(newRow);
            }
        }

        // Append only the new data (not already existing) to the file
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename, true))) {
            for (String newLine : newLines) {
                writer.println(newLine);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void loadSavedData() {
        loadSEM1Data("SEM1DAT.txt", SEM1GRADE);
        loadSEM2Data("SEM2DAT.txt", SEM2GRADE);
    }

    private void loadSEM1Data(String fileName, javax.swing.JTable table) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            DefaultTableModel model = (DefaultTableModel) table.getModel();
            model.setRowCount(0); // Clear the table before loading new data
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split("\\s+");
                
                if (data.length >= 8 && data[0].equals(userID)) {
                    Object[] rowData = new Object[]{data[2], data[3], data[4], data[5], data[6], data[7]};
                    model.addRow(rowData);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    private void loadSEM2Data(String fileName, javax.swing.JTable table) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            DefaultTableModel model = (DefaultTableModel) table.getModel();
            model.setRowCount(0); // Clear the table before loading new data
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split("\\s+");
                
                if (data.length >= 8 && data[0].equals(userID)) {
                    Object[] rowData = new Object[]{data[2], data[3], data[4], data[5], data[6], data[7]};
                    model.addRow(rowData);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroupCheckBoxes = new javax.swing.ButtonGroup();
        jPanel1 = new javax.swing.JPanel();
        NAME = new javax.swing.JLabel();
        LOGOUT = new javax.swing.JButton();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        LABEL1 = new javax.swing.JLabel();
        LABEL2 = new javax.swing.JLabel();
        QUIZPER = new javax.swing.JComboBox<>();
        EXAMPER = new javax.swing.JComboBox<>();
        PTPER = new javax.swing.JComboBox<>();
        LABEL5 = new javax.swing.JLabel();
        LABEL4 = new javax.swing.JLabel();
        LABEL3 = new javax.swing.JLabel();
        QUIZITEM = new javax.swing.JTextField();
        EXAMITEM = new javax.swing.JTextField();
        PTITEM = new javax.swing.JTextField();
        LINE1 = new javax.swing.JSeparator();
        MODIFY = new javax.swing.JButton();
        SET = new javax.swing.JButton();
        LINE2 = new javax.swing.JSeparator();
        PT = new javax.swing.JTextField();
        LABEL6 = new javax.swing.JLabel();
        LABEL7 = new javax.swing.JLabel();
        MIDTERM = new javax.swing.JTextField();
        FINAL = new javax.swing.JTextField();
        LABEL8 = new javax.swing.JLabel();
        LABEL9 = new javax.swing.JLabel();
        QUIZ = new javax.swing.JTextField();
        LABEL10 = new javax.swing.JLabel();
        LINE3 = new javax.swing.JSeparator();
        LABEL11 = new javax.swing.JLabel();
        STUDENTID = new javax.swing.JComboBox<>();
        UPDATE = new javax.swing.JButton();
        DROP = new javax.swing.JButton();
        S1 = new javax.swing.JCheckBox();
        S2 = new javax.swing.JCheckBox();
        LAYER = new javax.swing.JLayeredPane();
        SEM2PANEL = new javax.swing.JPanel();
        SEM2 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        A = new javax.swing.JScrollPane();
        SEM2GRADE = new javax.swing.JTable();
        SEM1PANEL = new javax.swing.JPanel();
        SEM1 = new javax.swing.JLabel();
        B = new javax.swing.JScrollPane();
        SEM1GRADE = new javax.swing.JTable();
        jLabel3 = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        LINE4 = new javax.swing.JSeparator();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("StudentGradingSystem");
        setLocation(new java.awt.Point(380, 20));

        jPanel1.setBackground(new java.awt.Color(0, 153, 153));

        NAME.setFont(new java.awt.Font("Segoe UI", 1, 18)); // NOI18N
        NAME.setForeground(new java.awt.Color(255, 255, 255));
        NAME.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        NAME.setText("    ");
        NAME.setToolTipText("");

        LOGOUT.setBackground(new java.awt.Color(0, 102, 102));
        LOGOUT.setForeground(new java.awt.Color(255, 255, 255));
        LOGOUT.setText("LOG OUT");
        LOGOUT.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 2, true));
        LOGOUT.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                LOGOUTActionPerformed(evt);
            }
        });

        jLabel5.setIcon(new javax.swing.ImageIcon(getClass().getResource("/oop_project/icons8-plasmid-40.png"))); // NOI18N

        jLabel6.setForeground(new java.awt.Color(255, 255, 255));
        jLabel6.setText("STUDENT GRADING SYSTEM");

        LABEL1.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL1.setText("TOTAL ITEMS");

        LABEL2.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL2.setText("PERCENTAGE");

        QUIZPER.setBackground(new java.awt.Color(0, 153, 153));
        QUIZPER.setForeground(new java.awt.Color(255, 255, 255));
        QUIZPER.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "CHOOSE", "0", "5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", "100" }));
        QUIZPER.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        QUIZPER.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                QUIZPERActionPerformed(evt);
            }
        });

        EXAMPER.setBackground(new java.awt.Color(0, 153, 153));
        EXAMPER.setForeground(new java.awt.Color(255, 255, 255));
        EXAMPER.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "CHOOSE", "0", "5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", "100" }));
        EXAMPER.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));

        PTPER.setBackground(new java.awt.Color(0, 153, 153));
        PTPER.setForeground(new java.awt.Color(255, 255, 255));
        PTPER.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "CHOOSE", "0", "5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", "100" }));
        PTPER.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));

        LABEL5.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL5.setText("PERFORMANCE TASK:");

        LABEL4.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL4.setText("EXAM:");

        LABEL3.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL3.setText("QUIZ:");

        MODIFY.setBackground(new java.awt.Color(0, 153, 153));
        MODIFY.setText("MODIFY");
        MODIFY.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        MODIFY.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                MODIFYActionPerformed(evt);
            }
        });

        SET.setBackground(new java.awt.Color(0, 153, 153));
        SET.setText("SET");
        SET.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        SET.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SETActionPerformed(evt);
            }
        });

        PT.setHorizontalAlignment(javax.swing.JTextField.CENTER);

        LABEL6.setFont(new java.awt.Font("Courier New", 1, 12)); // NOI18N
        LABEL6.setText("PERFORMANCE TASK ");

        LABEL7.setFont(new java.awt.Font("Courier New", 1, 12)); // NOI18N
        LABEL7.setText("MIDTERM EXAM ");

        MIDTERM.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        MIDTERM.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                MIDTERMActionPerformed(evt);
            }
        });

        FINAL.setHorizontalAlignment(javax.swing.JTextField.CENTER);

        LABEL8.setFont(new java.awt.Font("Courier New", 1, 12)); // NOI18N
        LABEL8.setText("FINAL EXAM ");

        LABEL9.setFont(new java.awt.Font("Courier New", 1, 12)); // NOI18N
        LABEL9.setText("TOTAL QUIZ ");

        QUIZ.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        QUIZ.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                QUIZActionPerformed(evt);
            }
        });

        LABEL10.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL10.setText("SCORES:");

        LABEL11.setFont(new java.awt.Font("Courier New", 1, 14)); // NOI18N
        LABEL11.setText("STUDENT ID ");

        STUDENTID.setBackground(new java.awt.Color(0, 153, 153));
        STUDENTID.setForeground(new java.awt.Color(255, 255, 255));
        STUDENTID.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "CHOOSE" }));
        STUDENTID.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        STUDENTID.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                STUDENTIDActionPerformed(evt);
            }
        });

        UPDATE.setBackground(new java.awt.Color(0, 153, 153));
        UPDATE.setText("Update");
        UPDATE.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        UPDATE.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                UPDATEActionPerformed(evt);
            }
        });

        DROP.setBackground(new java.awt.Color(0, 153, 153));
        DROP.setText("Drop");
        DROP.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 3, true));
        DROP.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DROPActionPerformed(evt);
            }
        });

        buttonGroupCheckBoxes.add(S1);
        S1.setText("Semester 1");
        S1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                S1ActionPerformed(evt);
            }
        });

        buttonGroupCheckBoxes.add(S2);
        S2.setText("Semester 2");
        S2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                S2ActionPerformed(evt);
            }
        });

        SEM2PANEL.setBackground(new java.awt.Color(0, 153, 153));

        SEM2.setFont(new java.awt.Font("Segoe UI Black", 0, 14)); // NOI18N
        SEM2.setText("SEMESTER 2");

        jLabel4.setIcon(new javax.swing.ImageIcon(getClass().getResource("/oop_project/icons8-semester-30.png"))); // NOI18N

        SEM2GRADE.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "Semester", "Student ID", "Total Quiz", "Toatal Exam", "Performance Task", "Grade"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }
        });
        A.setViewportView(SEM2GRADE);

        javax.swing.GroupLayout SEM2PANELLayout = new javax.swing.GroupLayout(SEM2PANEL);
        SEM2PANEL.setLayout(SEM2PANELLayout);
        SEM2PANELLayout.setHorizontalGroup(
            SEM2PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(SEM2PANELLayout.createSequentialGroup()
                .addGroup(SEM2PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(SEM2PANELLayout.createSequentialGroup()
                        .addGap(50, 50, 50)
                        .addComponent(A, javax.swing.GroupLayout.PREFERRED_SIZE, 615, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(SEM2PANELLayout.createSequentialGroup()
                        .addGap(301, 301, 301)
                        .addComponent(SEM2, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(102, Short.MAX_VALUE))
            .addGroup(SEM2PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(SEM2PANELLayout.createSequentialGroup()
                    .addGap(402, 402, 402)
                    .addComponent(jLabel4, javax.swing.GroupLayout.PREFERRED_SIZE, 42, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(323, Short.MAX_VALUE)))
        );
        SEM2PANELLayout.setVerticalGroup(
            SEM2PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(SEM2PANELLayout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addComponent(SEM2, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(A, javax.swing.GroupLayout.PREFERRED_SIZE, 183, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(14, Short.MAX_VALUE))
            .addGroup(SEM2PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(SEM2PANELLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jLabel4, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(202, Short.MAX_VALUE)))
        );

        SEM1PANEL.setBackground(new java.awt.Color(0, 153, 153));

        SEM1.setFont(new java.awt.Font("Segoe UI Black", 0, 14)); // NOI18N
        SEM1.setText("SEMESTER 1");

        SEM1GRADE.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(255, 255, 255), 2, true));
        SEM1GRADE.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "Semester", "Student ID", "Total Quiz", "Total Exam", "Performance Task", "Grade"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }
        });
        B.setViewportView(SEM1GRADE);

        jLabel3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/oop_project/icons8-semester-30.png"))); // NOI18N

        javax.swing.GroupLayout SEM1PANELLayout = new javax.swing.GroupLayout(SEM1PANEL);
        SEM1PANEL.setLayout(SEM1PANELLayout);
        SEM1PANELLayout.setHorizontalGroup(
            SEM1PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(SEM1PANELLayout.createSequentialGroup()
                .addGap(50, 50, 50)
                .addGroup(SEM1PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(B, javax.swing.GroupLayout.PREFERRED_SIZE, 615, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(SEM1PANELLayout.createSequentialGroup()
                        .addComponent(SEM1, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel3)
                        .addGap(233, 233, 233)))
                .addContainerGap(102, Short.MAX_VALUE))
        );
        SEM1PANELLayout.setVerticalGroup(
            SEM1PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(SEM1PANELLayout.createSequentialGroup()
                .addGap(17, 17, 17)
                .addGroup(SEM1PANELLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(SEM1)
                    .addComponent(jLabel3))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(B, javax.swing.GroupLayout.PREFERRED_SIZE, 183, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        LAYER.setLayer(SEM2PANEL, javax.swing.JLayeredPane.DEFAULT_LAYER);
        LAYER.setLayer(SEM1PANEL, javax.swing.JLayeredPane.DEFAULT_LAYER);

        javax.swing.GroupLayout LAYERLayout = new javax.swing.GroupLayout(LAYER);
        LAYER.setLayout(LAYERLayout);
        LAYERLayout.setHorizontalGroup(
            LAYERLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(LAYERLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(SEM1PANEL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(LAYERLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, LAYERLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(SEM2PANEL, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addContainerGap()))
        );
        LAYERLayout.setVerticalGroup(
            LAYERLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(LAYERLayout.createSequentialGroup()
                .addComponent(SEM1PANEL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 32, Short.MAX_VALUE))
            .addGroup(LAYERLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(LAYERLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(SEM2PANEL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(26, Short.MAX_VALUE)))
        );

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/oop_project/icons8-report-card-20.png"))); // NOI18N

        jLabel2.setIcon(new javax.swing.ImageIcon(getClass().getResource("/oop_project/icons8-id-verified-20.png"))); // NOI18N

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(170, 170, 170)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(225, 225, 225)
                        .addComponent(LABEL2)
                        .addGap(94, 94, 94)
                        .addComponent(LABEL1))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(LABEL4, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(LABEL5)
                            .addComponent(LABEL3, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(40, 40, 40)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(QUIZPER, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(EXAMPER, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(PTPER, javax.swing.GroupLayout.PREFERRED_SIZE, 153, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(48, 48, 48)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(QUIZITEM, javax.swing.GroupLayout.PREFERRED_SIZE, 129, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(EXAMITEM, javax.swing.GroupLayout.PREFERRED_SIZE, 129, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(PTITEM, javax.swing.GroupLayout.PREFERRED_SIZE, 129, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(28, 28, 28)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(MODIFY, javax.swing.GroupLayout.PREFERRED_SIZE, 98, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(SET, javax.swing.GroupLayout.PREFERRED_SIZE, 98, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addGap(0, 94, Short.MAX_VALUE))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(57, 57, 57)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(49, 49, 49)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addGroup(jPanel1Layout.createSequentialGroup()
                                        .addComponent(LABEL10, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jLabel1)
                                        .addGap(56, 56, 56)
                                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(LABEL9)
                                            .addComponent(QUIZ, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGap(39, 39, 39)
                                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                                .addComponent(FINAL, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(34, 34, 34))
                                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                                .addComponent(LABEL8)
                                                .addGap(23, 23, 23))))
                                    .addGroup(jPanel1Layout.createSequentialGroup()
                                        .addComponent(LABEL11)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jLabel2)
                                        .addGap(49, 49, 49)
                                        .addComponent(STUDENTID, javax.swing.GroupLayout.PREFERRED_SIZE, 94, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(42, 42, 42)
                                        .addComponent(UPDATE, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                .addGap(12, 12, 12)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                        .addComponent(DROP, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(18, 18, 18)
                                        .addComponent(S1, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(S2, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                            .addGroup(jPanel1Layout.createSequentialGroup()
                                                .addComponent(LABEL7)
                                                .addGap(32, 32, 32))
                                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, jPanel1Layout.createSequentialGroup()
                                                .addGap(16, 16, 16)
                                                .addComponent(MIDTERM, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)))
                                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(LABEL6)
                                            .addGroup(jPanel1Layout.createSequentialGroup()
                                                .addGap(23, 23, 23)
                                                .addComponent(PT, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                        .addGap(31, 31, 31))))
                            .addComponent(LINE4)
                            .addComponent(LINE3, javax.swing.GroupLayout.PREFERRED_SIZE, 755, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(70, 70, 70))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                .addGroup(jPanel1Layout.createSequentialGroup()
                                    .addComponent(jLabel5)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(jLabel6)
                                        .addGroup(jPanel1Layout.createSequentialGroup()
                                            .addComponent(NAME, javax.swing.GroupLayout.PREFERRED_SIZE, 484, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addGap(119, 119, 119)
                                            .addComponent(LOGOUT, javax.swing.GroupLayout.PREFERRED_SIZE, 96, javax.swing.GroupLayout.PREFERRED_SIZE))))
                                .addComponent(LINE1, javax.swing.GroupLayout.PREFERRED_SIZE, 735, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGap(62, 62, 62)
                                .addComponent(LAYER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(LINE2, javax.swing.GroupLayout.PREFERRED_SIZE, 802, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(14, 14, 14)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel5)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(13, 13, 13)
                        .addComponent(jLabel6)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(NAME, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(LOGOUT, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(LINE1, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(LABEL2)
                            .addComponent(LABEL1))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(LABEL3)
                                    .addComponent(QUIZPER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(EXAMPER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(LABEL4)
                                    .addComponent(EXAMITEM, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(PTPER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(LABEL5)
                                    .addComponent(PTITEM)))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(QUIZITEM, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(0, 0, Short.MAX_VALUE))))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(SET, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(MODIFY, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(6, 6, 6)))
                .addGap(18, 18, Short.MAX_VALUE)
                .addComponent(LINE2, javax.swing.GroupLayout.PREFERRED_SIZE, 7, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(LABEL7)
                        .addComponent(LABEL8)
                        .addComponent(LABEL9))
                    .addComponent(LABEL6))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(QUIZ, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(FINAL, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(PT, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(MIDTERM, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(LABEL10)))
                    .addComponent(jLabel1))
                .addGap(18, 18, 18)
                .addComponent(LINE3, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel2)
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(STUDENTID)
                        .addComponent(UPDATE)
                        .addComponent(DROP, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(LABEL11)
                        .addComponent(S2)
                        .addComponent(S1)))
                .addGap(18, 18, 18)
                .addComponent(LINE4, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(LAYER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    private void LOGOUTActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_LOGOUTActionPerformed
        // Open the FACADE frame
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                dispose();
                new FACADE().setVisible(true);
            }
        });
    }//GEN-LAST:event_LOGOUTActionPerformed

    private void MODIFYActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MODIFYActionPerformed
        disableComponents(false);
        enableComponents(true);
    }//GEN-LAST:event_MODIFYActionPerformed

    private void SETActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SETActionPerformed

    }//GEN-LAST:event_SETActionPerformed

    private void DROPActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DROPActionPerformed
        if(S1.isSelected()){
            DefaultTableModel model = (DefaultTableModel) SEM1GRADE.getModel();
            int[] rows = SEM1GRADE.getSelectedRows();

            if (rows.length > 0) {
                for (int i = rows.length - 1; i >= 0; i--) {
                    String studentID = model.getValueAt(rows[i], 1).toString(); 
                    
                    model.removeRow(rows[i]);

                    // Call the update method after modifying the table
                    updateSEM1DATA();
                    
                    removeMatchingLineFromFile(studentID, "SEM1DAT.txt");
                    
                    JOptionPane.showMessageDialog(this, "Data successfully removed from the list.");
                }
            } else {
                JOptionPane.showMessageDialog(this, "No Data found. Please select a Row.");
            }
        }else{
            DefaultTableModel model = (DefaultTableModel) SEM2GRADE.getModel();
            int[] rows = SEM2GRADE.getSelectedRows();

              if (rows.length > 0) {
                for (int i = rows.length - 1; i >= 0; i--) {
                    String studentID = model.getValueAt(rows[i], 1).toString(); 
                    
                    model.removeRow(rows[i]);

                    // Call the update method after modifying the table
                    updateSEM1DATA();
                    
                    removeMatchingLineFromFile(studentID, "SEM2DAT.txt");
                    
                    JOptionPane.showMessageDialog(this, "Data successfully removed from the list.");
                }
            } else {
                JOptionPane.showMessageDialog(this, "No Data found. Please select a Row.");
            }            
        }
    }//GEN-LAST:event_DROPActionPerformed

    private void UPDATEActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_UPDATEActionPerformed
        // Check if QUIZ, MIDTERM, FINAL, and PT fields are empty
        if (!areFieldsFilled()) {
            JOptionPane.showMessageDialog(null, "Please fill out all the fields.");
            return;
        }

        // Check if QUIZ, MIDTERM, FINAL, and PT fields are numbers
        if (!areFieldsNumbers()) {
            JOptionPane.showMessageDialog(null, "Accepted scores are limited to positive number only.");
            return;
        }

        double quiz = Double.parseDouble(QUIZ.getText());
        double exam1 = Double.parseDouble(MIDTERM.getText());
        double exam2 = Double.parseDouble(FINAL.getText());
        double pt = Double.parseDouble(PT.getText());

        // Validation based on entered values
        if ((exam1 + exam2) > Double.parseDouble(EXAMITEM.getText())) {
            JOptionPane.showMessageDialog(null, "Total score in Exam exceeds the Total Items");
            return;
        }

        if (quiz > Double.parseDouble(QUIZITEM.getText())) {
            JOptionPane.showMessageDialog(null, "Total score in Quiz exceeds the Total Items.");
            return;
        }

        if (pt > Double.parseDouble(PTITEM.getText())) {
            JOptionPane.showMessageDialog(null, "Performance task score exceeds the Total Items.");
            return;
        }

        // Check if STUDENTID is selected
        if (STUDENTID.getSelectedIndex() == 0) {
            JOptionPane.showMessageDialog(null, "Student ID not specified.");
            return;
        }

        String selectedStudentID = STUDENTID.getSelectedItem().toString();
        boolean s1Checked = S1.isSelected();
        boolean s2Checked = S2.isSelected();
        
        if (s1Checked || s2Checked) {
            double SCORE1 = (quiz / Double.parseDouble(QUIZITEM.getText())) * (Double.parseDouble(QUIZPER.getSelectedItem().toString())*.01);
            double SCORE2 = (((exam1 + exam2) / Double.parseDouble(EXAMITEM.getText())) * (Double.parseDouble(EXAMPER.getSelectedItem().toString()))*.01);
            double SCORE3 = (pt / Double.parseDouble(PTITEM.getText())) * (Double.parseDouble(PTPER.getSelectedItem().toString())*.01);

            double finalGrade = (SCORE1) + (SCORE2) + (SCORE3);

            String FS1 = String.format("%.2f", SCORE1 * 100);
            String FS2 = String.format("%.2f", SCORE2 * 100);
            String FS3 = String.format("%.2f", SCORE3 * 100);
            String FS4 = String.format("%.2f", finalGrade * 100);
            
            if (s1Checked) {
                // Store data in SEM1GRADE table
                DefaultTableModel model = (DefaultTableModel) SEM1GRADE.getModel();
                
                if (isStudentIDAlreadyExists(model, selectedStudentID)) {
                    JOptionPane.showMessageDialog(null, "This Student's grade is already recorded. Can't duplicate data.");
                    STUDENTID.setSelectedIndex(0);
                    return; // Exit without adding duplicate data
                }
                
                Object[] row = {1, selectedStudentID, FS1, FS2, FS3, FS4};
                model.addRow(row);
                
                updateSEM1DATA();
                
                saveDataToFile(getSem1GradeData(), "SEM1DAT.txt");
                
                QUIZ.setText("");
                MIDTERM.setText("");
                FINAL.setText("");
                PT.setText(""); 
                
                JOptionPane.showMessageDialog(null, "Data successfully added to the list.");
            } else if (s2Checked) {
                // Store data in SEM2GRADE table
                DefaultTableModel model = (DefaultTableModel) SEM2GRADE.getModel();
                
                if (isStudentIDAlreadyExists(model, selectedStudentID)) {
                    JOptionPane.showMessageDialog(null, "This Student's grade is already recorded. Can't duplicate data.");
                    STUDENTID.setSelectedIndex(0);
                    return; // Exit without adding duplicate data
                }
                
                Object[] row = {2, selectedStudentID, FS1, FS2, FS3, FS4};
                model.addRow(row);
                
                updateSEM2DATA();
                
                saveDataToFile(getSem2GradeData(), "SEM2DAT.txt");
                
                QUIZ.setText("");
                MIDTERM.setText("");
                FINAL.setText("");
                PT.setText("");
                
                JOptionPane.showMessageDialog(null, "Data successfully added to the list.");
            }
               
            STUDENTID.setSelectedIndex(0);
        } else {
            JOptionPane.showMessageDialog(null, "Please select either SEM1 or SEM2");
        }
    }//GEN-LAST:event_UPDATEActionPerformed

    private void STUDENTIDActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_STUDENTIDActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_STUDENTIDActionPerformed

    private void MIDTERMActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MIDTERMActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_MIDTERMActionPerformed

    private void S2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_S2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_S2ActionPerformed

    private void S1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_S1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_S1ActionPerformed

    private void QUIZPERActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_QUIZPERActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_QUIZPERActionPerformed

    private void QUIZActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_QUIZActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_QUIZActionPerformed
    
    private boolean areFieldsFilled() {
        // Check if the required fields are filled, modify this based on your specific fields
        return !QUIZ.getText().isEmpty() &&
               !MIDTERM.getText().isEmpty() &&
               !FINAL.getText().isEmpty() &&
               !PT.getText().isEmpty();
    }
    
    private boolean areFieldsNumbers() {
        // Check if the required fields contain numeric values
        try {
            double quizValue = Double.parseDouble(QUIZ.getText());
            double exam1 = Double.parseDouble(MIDTERM.getText());
            double exam2 = Double.parseDouble(FINAL.getText());
            double examValue = exam1 + exam2;
            double ptValue = Double.parseDouble(PT.getText());

            return quizValue >= 0 && examValue >= 0 && ptValue >= 0;
        } catch (NumberFormatException e) {
            // If any field is not a number or empty
            return false;
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(StudentGradingSystem.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(StudentGradingSystem.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(StudentGradingSystem.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(StudentGradingSystem.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new StudentGradingSystem("NOT FOUND", "NOT FOUND", "NOT FOUND", "NOT FOUND").setVisible(true);
            }
        });
    }
   
    private void removeMatchingLineFromFile(String studentID, String filename) {
        try {
            File inputFile = new File(filename);
            File tempFile = new File("tempFile.txt");

            BufferedReader reader = new BufferedReader(new FileReader(inputFile));
            BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile));

            String currentLine;

            while ((currentLine = reader.readLine()) != null) {
                // Splitting the line by space assuming a space-separated format
                String[] parts = currentLine.split("\\s+");

                // Check if the line matches the userID and studentID
                if (parts.length >= 4 && parts[0].equals(userID) && parts[3].equals(studentID)) {
                    continue; // Skip writing this line to the temporary file
                }

                // Write non-matching lines to the temporary file
                writer.write(currentLine + System.getProperty("line.separator"));
            }

            writer.close();
            reader.close();

            // Replace the original file with the temporary file
            if (!inputFile.delete()) {
                System.out.println("Could not delete the original file.");
                return;
            }

            if (!tempFile.renameTo(inputFile)) {
                System.out.println("Could not rename the temporary file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
   
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JScrollPane A;
    private javax.swing.JScrollPane B;
    private javax.swing.JButton DROP;
    private javax.swing.JTextField EXAMITEM;
    private javax.swing.JComboBox<String> EXAMPER;
    private javax.swing.JTextField FINAL;
    private javax.swing.JLabel LABEL1;
    private javax.swing.JLabel LABEL10;
    private javax.swing.JLabel LABEL11;
    private javax.swing.JLabel LABEL2;
    private javax.swing.JLabel LABEL3;
    private javax.swing.JLabel LABEL4;
    private javax.swing.JLabel LABEL5;
    private javax.swing.JLabel LABEL6;
    private javax.swing.JLabel LABEL7;
    private javax.swing.JLabel LABEL8;
    private javax.swing.JLabel LABEL9;
    private javax.swing.JLayeredPane LAYER;
    private javax.swing.JSeparator LINE1;
    private javax.swing.JSeparator LINE2;
    private javax.swing.JSeparator LINE3;
    private javax.swing.JSeparator LINE4;
    private javax.swing.JButton LOGOUT;
    private javax.swing.JTextField MIDTERM;
    private javax.swing.JButton MODIFY;
    private javax.swing.JLabel NAME;
    private javax.swing.JTextField PT;
    private javax.swing.JTextField PTITEM;
    private javax.swing.JComboBox<String> PTPER;
    private javax.swing.JTextField QUIZ;
    private javax.swing.JTextField QUIZITEM;
    private javax.swing.JComboBox<String> QUIZPER;
    private javax.swing.JCheckBox S1;
    private javax.swing.JCheckBox S2;
    private javax.swing.JLabel SEM1;
    private javax.swing.JTable SEM1GRADE;
    private javax.swing.JPanel SEM1PANEL;
    private javax.swing.JLabel SEM2;
    private javax.swing.JTable SEM2GRADE;
    private javax.swing.JPanel SEM2PANEL;
    private javax.swing.JButton SET;
    private javax.swing.JComboBox<String> STUDENTID;
    private javax.swing.JButton UPDATE;
    private javax.swing.ButtonGroup buttonGroupCheckBoxes;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    // End of variables declaration//GEN-END:variables
}